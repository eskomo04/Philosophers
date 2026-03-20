/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:26:17 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/20 04:27:26 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	sleep_philo(t_philo *philo)
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
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is eating\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	think_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is thinking\n", ft_time_ms(philo), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}