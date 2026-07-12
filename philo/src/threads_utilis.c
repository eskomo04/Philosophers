/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: essia <essia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:26:17 by eskomo            #+#    #+#             */
/*   Updated: 2026/07/12 18:21:02 by essia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static bool	evan_right_fork_first(t_philo *philo)
{
	if (someone_died_or_full(philo))
		return (false);
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	if (someone_died_or_full(philo))
	{
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		return (false);
	}
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	return (true);
}

static bool	odd_left_fork_first(t_philo *philo)
{
	if (someone_died_or_full(philo))
		return (false);
	pthread_mutex_lock(&philo->left_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	if (someone_died_or_full(philo))
	{
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		return (false);
	}
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	ft_print_safe(philo, "has taken a fork");
	return (true);
}

void	eat(t_philo *philo)
{
	bool	success;

	success = false;
	if (philo->philo_id % 2 == 0)
		success = evan_right_fork_first(philo);
	else
		success = odd_left_fork_first(philo);
	if (!success)
		return ;
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

int	should_stop_eating(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->meal_mutex);
	stop = (philo->data->num_of_times_to_eat != -1
			&& philo->meals >= philo->data->num_of_times_to_eat);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (stop);
}
