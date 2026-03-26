/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eskomo <eskomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:19:32 by eskomo            #+#    #+#             */
/*   Updated: 2026/03/26 03:38:06 by eskomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_max_int(char *str)
{
	long long	num;

	num = 0;
	while (*str)
	{
		if (!is_digit(str))
			return (false);
		num = num * 10 + (*str - '0');
		if (num > INT_MAX)
			return (false);
		str++;
	}
	return (true);
}


bool	check_input(int argc, char **argv)
{
	if (argc > 6 || argc < 5 || ft_atoi(argv[1]) <= 0)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	else if (!check_max_int(argv[1]) || !check_max_int(argv[2])
		|| !check_max_int(argv[3]) || !check_max_int(argv[4])
		|| (argv[5] && !check_max_int(argv[5])))
	{
		printf("Error: Arguments must be less than 2147483647/INT_MAX\n");
		return (false);
	}
	else if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0 || (argv[5] && ft_atoi(argv[5]) <= 0))
	{
		printf("Error: Arguments must be positive\n");
		return (false);
	}
	return (true);
}
