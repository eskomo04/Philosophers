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

static bool	someone_died_or_full_locked(t_philo *philo)
{
	bool	someone_died;
	bool	philos_full;

	someone_died = philo->data->death.someone_died;
	philos_full = philo->data->death.philos_full;
	if (someone_died || philos_full)
		return (true);
	return (false);
}

bool	someone_died_or_full(t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->data->death.print_mutex);
	result = someone_died_or_full_locked(philo);
	pthread_mutex_unlock(&philo->data->death.print_mutex);
	return (result);
}

void	ft_print_safe(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->death.print_mutex);
	if (someone_died_or_full_locked(philo))
	{
		pthread_mutex_unlock(&philo->data->death.print_mutex);
		return ;
	}
	printf("%lld %d %s\n", ft_time_ms(philo), philo->philo_id, message);
	pthread_mutex_unlock(&philo->data->death.print_mutex);
	return ;
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	ft_safe_usleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	return (NULL);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philos == 1)
		return (one_philo(philo));
	while (!should_stop_eating(philo))
	{
		eat(philo);
		if (someone_died_or_full(philo))
			break ;
		ft_print_safe(philo, "is sleeping");
		ft_safe_usleep(philo->data->time_to_sleep, philo);
		if (someone_died_or_full(philo))
			break ;
		think_philo(philo);
		if (someone_died_or_full(philo))
			break ;
	}
	return (NULL);
}
