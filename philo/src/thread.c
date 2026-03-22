/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:45:35 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/20 04:45:35 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	ft_print_safe(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->death.death_mutex);
	if (philo->data->death.someone_died)
	{
		pthread_mutex_unlock(&philo->data->death.death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death.death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", ft_time_ms(philo), philo->philo_id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return ;
}

static void *one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	return (NULL);
}

bool	someone_died_or_full(t_philo *philo)
{
	bool	someone_died;
	bool	philos_full;

	pthread_mutex_lock(&philo->data->death.death_mutex);
	someone_died = philo->data->death.someone_died;
	philos_full = philo->data->death.philos_full;
	pthread_mutex_unlock(&philo->data->death.death_mutex);
	if (someone_died || philos_full)
		return (true);
	return (false);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
		return (one_philo(philo));
	while (1)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->data->num_of_times_to_eat != -1
			&& philo->meals >= philo->data->num_of_times_to_eat)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		eat(philo);
		if (someone_died_or_full(philo))
			break ;
		sleep_philo(philo);
		if (someone_died_or_full(philo))
			break ;
		think_philo(philo);
		if (someone_died_or_full(philo))
			break ;
	}
	return (NULL);
}
