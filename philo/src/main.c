/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:09:03 by eskomo            #+#    #+#             */
/*   Updated: 2026/04/03 05:09:03 by eskomo           ###   ########.fr       */
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

static void	clean_up(t_philo *philo, t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	destroy_mutexes(forks, data->num_of_philos);
	pthread_mutex_destroy(&data->death.print_mutex);
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&philo[i++].meal_mutex);
	free(philo);
	free(forks);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	t_fork	*forks;
	int		i;

	if (!check_input(argc, argv))
		return (1);
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
	if (!philo || !forks)
	{
		if (philo)
			free(philo);
		if (forks)
			free(forks);
		return (1);
	}
	init_data(&data, argv);
	init_forks(forks, ft_atoi(argv[1]));
	init_philo(philo, &data, forks);
	monitoring(philo);
	while (i < data.num_of_philos)
		pthread_join(philo[i++].thread_id, NULL);
	clean_up(philo, forks, &data);
	return (0);
}
