/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:27:54 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/24 09:25:55 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	quit_in_err(t_data *data, int err_num)
{
	unvalid_args(err_num);
	cleanup(data);
	return (1);
}

void	print_err(const char *err, const char *color)
{
	if (color)
		write(2, color, ft_strlen(color));
	write(2, err, ft_strlen(err));
	if (color)
		write(2, RESET, ft_strlen(RESET));
}

int	validate_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	unvalid_args(int err_n)
{
	if (err_n == 8)
		return (print_err("malloc failed: returned NULL\n", NULL));
	if (err_n == 1)
		print_err("Error:\nInvalid number of arguments. Expected format:\n\n",
			RED);
	if (err_n == 2)
		print_err("Error:\nAll arguments must be numeric. Expected format:\n\n",
			RED);
	if (err_n == 3)
		print_err("Error:\nNumber_of_times_each_philo_must_eat must be "
			"in range of intgers. Expected format:\n\n",
			RED);
	if (err_n == 4)
		print_err("Error:\nYou should have at least one philosopher. "
			"Expected format:\n\n",
			RED);
	if (err_n == 5)
		return (print_err("Failed to initialize mutex", NULL));
	if (err_n == 6)
		return (print_err("Failed to creat thread", NULL));
	if (err_n == 7)
		return (print_err("Failure : pthread_join", NULL));
	print_err("./philo <number_of_philosophers> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [number_of_times_each_philo_must_eat]\n\n",
		GREEN);
}

bool	check_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
		return (unvalid_args(1), true);
	if (!validate_args(av))
		return (unvalid_args(2), true);
	return (false);
}
