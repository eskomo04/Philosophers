/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:37:22 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/04 05:22:52 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc == 5)
	{
		philo.data->num_of_philos = ft_atoi(argv[1]);
		philo.data->time_to_die = ft_atoi(argv[2]);
		philo.data->time_to_eat = ft_atoi(argv[3]);
		philo.data->time_to_sleep = ft_atoi(argv[4]);
		philo.data->num_of_times_to_eat = ft_atoi(argv[5]);
	}
}
