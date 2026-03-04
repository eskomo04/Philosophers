/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:37:22 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/04 06:34:43 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	t_fork	*forks;

	if (argc == 6)
	{
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
		init_data(&data, argv);
		init_forks(forks, ft_atoi(argv[1]));
		init_philo(philo, &data, forks);
	}
}
