/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:37:22 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/07 01:43:25 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	destroy_mutexes(t_fork *forks, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&forks[i].fork_mutex);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	t_fork	*forks;
	int		i;

	i = 0;
	if (argc == 6)
	{
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
		init_data(&data, argv);
		init_forks(forks, ft_atoi(argv[1]));
		init_philo(philo, &data, forks);
		while (i < data.num_of_philos)
			pthread_join(philo[i++].thread_id, NULL);
		destroy_mutexes(forks, data.num_of_philos);
		free(philo);
		free(forks);
	}
	else
		printf("Error: Wrong number of arguments\n");
}
