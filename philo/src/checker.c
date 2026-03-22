/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:19:32 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/20 07:04:47 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

bool	check_input(int argc, char **argv)
{
	if (argc > 6 || argc < 5 || ft_atoi(argv[1]) <= 0)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	else if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
	{
		printf("Error: Argument must be positive\n");
		return (false);
	}
	else if (argv[5] && ft_atoi(argv[5]) <= 0)
	{
		printf("Error: num_of_times_to_eat must be positive\n");
		return (false);
	}
	return (true);
}
