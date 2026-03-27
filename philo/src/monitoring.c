/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 04:35:46 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/27 04:19:11 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	*someone_died(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->death.print_mutex);
	philo->data->death.someone_died = true;
	printf("%lld %d died\n", ft_time_ms(&philo[i]), philo[i].philo_id);
	pthread_mutex_unlock(&philo->data->death.print_mutex);
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

static void	*monitor_function(void *philo)
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
			pthread_mutex_lock(&philos->data->death.print_mutex);
			philos->data->death.philos_full = true;
			pthread_mutex_unlock(&philos->data->death.print_mutex);
			break ;
		}
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos->data->num_of_times_to_eat == -1
			|| philos[i].meals < philos->data->num_of_times_to_eat)
			if (ft_get_time() - philos[i].last_meal > philos->data->time_to_die)
				return (pthread_mutex_unlock(&philos[i].meal_mutex),
					someone_died(philos, i));
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (NULL);
}

void	monitoring(t_philo *philo)
{
	pthread_t	monitor_thread;

	pthread_create(&monitor_thread, NULL, monitor_function, philo);
	pthread_join(monitor_thread, NULL);
}
