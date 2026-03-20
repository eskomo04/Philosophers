/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:24:48 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/20 04:24:48 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_died
{
	pthread_mutex_t	death_mutex;
	bool			someone_died;
	bool			philos_full;
}			t_died;

typedef struct s_data
{
	pthread_mutex_t	print_mutex;
	t_died			death;
	long long		start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_times_to_eat;
	long			num_of_philos;
}			t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				fork_id;
}			t_fork;

typedef struct s_philo
{
	pthread_mutex_t	meal_mutex;
	pthread_t		thread_id;
	long long		last_meal;
	int				philo_id;
	int				meals;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
}			t_philo;

// main.c
void	monitoring(t_philo *philo);
void	*monitor_function(void *philo);

// utilis.c
int		ft_atoi(char *s);
long long	ft_time_ms(t_philo *philo);
long long	ft_get_time(void);

// init.c
void	init_forks(t_fork *forks, int num_of_forks);
void	init_philo(t_philo *philo, t_data *data, t_fork *forks);
void	init_data(t_data *data, char **arg);

// thread.c
void	*thread_function(void *arg);

// checker.c
bool	check_input(int argc, char **argv);

// threads_utilis.c
void	sleep_philo(t_philo *philo);
void	eat(t_philo *philo);
void	think_philo(t_philo *philo);

#endif