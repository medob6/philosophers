/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:26:01 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 17:09:32 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	check_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
		errExitEN(NULL, 1);
	if (!validate_args(av))
		errExitEN(NULL, 2);
}

void	get_data(t_data *data, char **args)
{
	data->start_date = get_time_ms();
	data->philos = NULL;
	data->philo_number = ft_atoi(args[1]);
	if (data->philo_number == 0)
		errExitEN(data, 4);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (data->philo_number <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		errExitEN(data, 2);
	if (args[5])
	{
		data->meals_per_philo = ft_atoi(args[5]);
		if (data->meals_per_philo <= 0)
			errExitEN(data, 3);
	}
	else
		data->meals_per_philo = -1;
}

void	init_locks(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink("/write_lock");
	sem_unlink("/death_lock");
	sem_unlink("/sim_lock");
	data->sem_stop = sem_open("/sim_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->sem_stop == SEM_FAILED)
		errExitEN(data, 5);
	data->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644,
			data->philo_number);
	if (data->forks == SEM_FAILED)
		errExitEN(data, 5);
	data->write_lock = sem_open("/write_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->write_lock == SEM_FAILED)
		errExitEN(data, 5);
	data->death_lock = sem_open("/death_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->death_lock == SEM_FAILED)
		errExitEN(data, 5);
}
