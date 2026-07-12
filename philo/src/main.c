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
	if (!setup(&philo, &data, &forks, argv))
		return (1);
	monitoring(philo);
	i = 0;
	while (i < data.num_of_philos)
		pthread_join(philo[i++].thread_id, NULL);
	clean_up(philo, forks, &data);
	return (0);
}
