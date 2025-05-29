/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:36:13 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 18:33:04 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_err(const char *err, const char *color)
{
	if (color)
		write(2, color, ft_strlen(color));
	write(2, err, ft_strlen(err));
	if (color)
		write(2, RESET, ft_strlen(RESET));
}

void	unvalid_args(int err_n)
{
	if (err_n == 8)
		return (print_err("malloc failed: returned NULL\n", NULL));
	if (err_n == 1)
		print_err("Error:\nInvalid number of arguments. Expected format:\n\n",
			RED);
	else if (err_n == 2)
		print_err("Error:\nAll arguments must be numeric. Expected format:\n\n",
			RED);
	else if (err_n == 3)
		print_err("Error:\nnumber_of_times_each_philo_must_eat must be "
					"a positive integer. Expected format:\n\n",
					RED);
	else if (err_n == 4)
		print_err("Error:\nYou must have at least one philosopher. Expected format:\n\n",
			RED);
	else if (err_n == 5)
		return (print_err("Failed to open semaphore\n", RED));
	else if (err_n == 6)
		return (print_err("Failed to create thread\n", RED));
	else if (err_n == 7)
		return (print_err("Failed to wait for processes\n", RED));
	print_err("./philo <number_of_philosophers> <time_to_die> <time_to_eat> "
				"<time_to_sleep> [number_of_times_each_philo_must_eat]\n\n",
				GREEN);
}

// void	wait_monitor(t_data *data)
// {
// 	int	s;

// 	s = 0;
// 	if (data->monitor_created)
// 	{
// 		s = pthread_join(data->monitor_id, NULL);
// 		if (s != 0)
// 			errExitEN(data, 7);
// 	}
// }

void	kill_all(t_data *data)
{
	size_t	j;

	sem_post(data->death_lock);
	j = 0;
	while (j < data->philo_number)
		kill(data->philos[j++].id, SIGTERM);
}

int	wait_philos(t_data *data)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < data->philo_number)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_all(data);
			break ;
		}
		i++;
	}
	return (0);
}

void	errExitEN(t_data *data, int err_num)
{
	if (err_num == 6)
		wait_philos(data);
	unvalid_args(err_num);
	cleanup(data);
	exit(EXIT_FAILURE);
}
