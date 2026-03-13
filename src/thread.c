/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+      +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/03/06 02:33:41 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/09 03:41:20 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"


static void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is sleeping\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	evan_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	odd_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

static void	eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		evan_right_fork_first(philo);
	else
		odd_left_fork_first(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is eating\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->num_of_times_to_eat > 0
			&& (philo->data->num_of_times_to_eat <= philo->meals))
			break ;
		pthread_mutex_lock(&philo->data->death.death_mutex);
		if (philo->data->death.someone_died)
		{
			pthread_mutex_unlock(&philo->data->death.death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death.death_mutex);
		eat(philo);
		sleep_philo(philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%lld %d is thinking\n", ft_time_ms(philo), philo->philo_id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	return (NULL);
}
