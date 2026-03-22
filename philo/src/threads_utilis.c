/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:26:17 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/22 05:12:28 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	sleep_philo(t_philo *philo)
{
	ft_print_safe(philo, "is sleeping");
	ft_safe_usleep(philo->data->time_to_sleep, philo);
}

static void	evan_right_fork_first(t_philo *philo)
{
	if (someone_died_or_full(philo))
		return ;
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	if (someone_died_or_full(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
}

static void	odd_left_fork_first(t_philo *philo)
{
	if (someone_died_or_full(philo))
		return ;
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	if (someone_died_or_full(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		evan_right_fork_first(philo);
	else
		odd_left_fork_first(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = ft_get_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_print_safe(philo, "is eating");
	ft_safe_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	think_philo(t_philo *philo)
{
	ft_print_safe(philo, "is thinking");
}
