/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 00:28:51 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/13 00:28:51 by eskomo           ###   ########.fr       */
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
	if (argc > 6 || argc < 5 || ft_atoi(argv[1]) <= 0)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
	init_data(&data, argv);
	init_forks(forks, ft_atoi(argv[1]));
	init_philo(philo, &data, forks);
	monitoring(philo);
	while (i < data.num_of_philos)
		pthread_join(philo[i++].thread_id, NULL);
	destroy_mutexes(forks, data.num_of_philos);
	pthread_mutex_destroy(&data.death.death_mutex);
	pthread_mutex_destroy(&data.print_mutex);
	i = 0;
	while (i < data.num_of_philos)
		pthread_mutex_destroy(&philo[i++].meal_mutex);
	free(philo);
	free(forks);
	return (0);
}

void	monitoring(t_philo *philo)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, monitor_function, philo);
	pthread_join(monitor_thread, NULL);
}

static void	*someone_died(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d died\n", ft_time_ms(philo), philo[i].philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death.death_mutex);
	philo->data->death.someone_died = true;
	pthread_mutex_unlock(&philo->data->death.death_mutex);
	return (NULL);
}

static bool	all_philos_full(t_philo *philo)
{
	int	i;

	if (philo->data->num_of_times_to_eat == -1)
		return (false);
	i = 0;
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (philo[i].meals < philo->data->num_of_times_to_eat)
		{
			pthread_mutex_unlock(&philo[i].meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (true);
}
void	*monitor_function(void *philo)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philo;
	i = 0;
	while (1)
	{
		if (i > philos->data->num_of_philos - 1)
			i = 0;
		if (all_philos_full(philos))
		{
			pthread_mutex_lock(&philos->data->death.death_mutex);
			philos->data->death.philos_full = true;
			pthread_mutex_unlock(&philos->data->death.death_mutex);
			break ;
		}
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (ft_get_time() - philos[i].last_meal > philos->data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (someone_died(philos, i));
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (NULL);
}
