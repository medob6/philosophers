/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:54:56 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/27 13:51:38 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	print_philo_state(const char *state, t_philo *philo)
// {
// 	time_t	timestamp;

// 	pthread_mutex_lock(&philo->shared_data->stop_mtx);
// 	if (philo->shared_data->simulation_stopped)
// 	{
// 		pthread_mutex_unlock(&philo->shared_data->stop_mtx);
// 		return ;
// 	}
// 	pthread_mutex_lock(&philo->shared_data->print_mtx);
// 	timestamp = get_time_ms() - philo->shared_data->start_date;
// 	printf("%zu %zu %s\n", timestamp, philo->index, state);
// 	pthread_mutex_unlock(&philo->shared_data->print_mtx);
// 	pthread_mutex_unlock(&philo->shared_data->stop_mtx);
// }

// void	philo_eat(t_philo philo)
// {
// 	printf("");
// 	usleep(data->time_to_eat);
// }

void	philo(t_data *data, int i)
{
	t_philo philo;
	philo = data->philos[i];
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return ;
}

void	creat_philo_prc(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		data->simulation_stopped = true;
		errExitEN(data, 6);
	}
	else if (pid == 0)
	{
		philo(data, i); // TODO : craet this function
		exit(0);
	}
	else
	{
		data->philos[i].id = pid;
	}
}

int	creat_philos(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_number);
	if (!data->philos)
		errExitEN(data, 8);
	i = 0;
	while (i < data->philo_number)
		creat_philo_prc(data, i++);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	check_args(ac, av);
	data = malloc(sizeof(t_data));
	if (!data)
		errExitEN(data, 8);
	get_data(data, av);
	creat_philos(data); // fix creat philo function then fix monitor philo function 
	monitor_philos(data);
	wait_philos(data);
	wait_monitor(data);
	cleanup(data);
	return (0);
}
