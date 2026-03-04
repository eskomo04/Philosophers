/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 02:12:46 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/04 05:23:54 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_data
{
	int				time_to_think;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				num_of_philos;
	bool			someone_died;
}					t_data;

typedef struct s_philo
{
	long			last_meal;
	t_data			*data;
}					t_philo;

/*******************FILES FUNCTION******************* */

// utilis.c
int					ft_atoi(char *s);

#endif