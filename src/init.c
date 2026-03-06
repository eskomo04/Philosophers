/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 06:25:54 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/06 01:08:10 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	init_forks(t_fork *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		forks[i].fork_id = i + 1;
		i++;
	}
}

/**
 * Init the philosopher structure with the data structure
 * and assign philosopher id
 */
void	init_philo(t_philo *philo, t_data *data, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].meals = 0;
		philo[i].data = data;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i - 1 + data->num_of_philos)
			% data->num_of_philos];
		i++;
	}
}

/**
 * Init the data structure with the command line arguments
 */
void	init_data(t_data *data, char **arg)
{
	data->num_of_philos = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	data->num_of_times_to_eat = ft_atoi(arg[5]);
}
