/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_maintain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 07:18:19 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/08 07:21:28 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	evan_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	printf("Philosopher %d has taken right fork %d\n", philo->philo_id,
		philo->right_fork->fork_id);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	printf("Philosopher %d has taken left fork %d\n", philo->philo_id,
		philo->left_fork->fork_id);
}

void	odd_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	printf("Philosopher %d has taken left fork %d\n", philo->philo_id,
		philo->left_fork->fork_id);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	printf("Philosopher %d has taken right fork %d\n", philo->philo_id,
		philo->right_fork->fork_id);
}
