/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 02:33:41 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/08 06:12:27 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = ft_get_time();
	philo->meals++;
	printf("Philosopher %d is eating\n", philo->philo_id);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

static void	sleep_philo(t_philo *philo)
{
	printf("Philosopher %d is sleeping\n", philo->philo_id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->someone_died
			|| (philo->data->num_of_times_to_eat <= philo->meals))
			break ;
		if (ft_get_time() - philo->last_meal > philo->data->time_to_die)
		{
			philo->data->someone_died = true;
			printf("Philo %d died\n", philo->philo_id);
			break ;
		}
		// if (philo->data->num_of_times_to_eat <= 0)
		// To-do in seperate file of checker functions
		// 	break ;
		eat(philo);
		sleep_philo(philo);
		//think(philo);
	}
	return (NULL);
}
