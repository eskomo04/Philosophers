/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 02:33:41 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/09 03:41:20 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	sleep_philo(t_philo *philo)
{
	printf("Philosopher %d is sleeping\n", philo->philo_id);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	evan_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	printf("Philosopher %d has taken right fork %d\n", philo->philo_id,
		philo->right_fork->fork_id);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	printf("Philosopher %d has taken left fork %d\n", philo->philo_id,
		philo->left_fork->fork_id);
}

static void	odd_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	printf("Philosopher %d has taken left fork %d\n", philo->philo_id,
		philo->left_fork->fork_id);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	printf("Philosopher %d has taken right fork %d\n", philo->philo_id,
		philo->right_fork->fork_id);
}

static void	eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		evan_right_fork_first(philo);
	else
		odd_left_fork_first(philo);
	philo->last_meal = ft_get_time();
	philo->meals++;
	usleep(philo->data->time_to_eat * 1000);
	printf("Philosopher %d is eating\n", philo->philo_id);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->num_of_times_to_eat <= philo->meals)
			break ;
		// if (philo->data->num_of_times_to_eat <= 0)
		// To-do in seperate file of checker functions
		// 	break ;
		eat(philo);
		sleep_philo(philo);
		//think(philo);
	}
	return (NULL);
}
