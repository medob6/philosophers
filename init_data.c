/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:30:15 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/24 18:59:11 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(t_data *data, char **args)
{
	data->shared_data = NULL;
	data->forks = NULL;
	data->philos = NULL;
	data->err_num = 0;
	data->shared_data = malloc(sizeof(t_shared_data));
	if (!data->shared_data)
		return (data->err_num = 8, 1);
	data->shared_data->start_date = get_time_ms();
	data->shared_data->simulation_stopped = false;
	data->shared_data->philo_number = ft_atoi(args[1]);
	if (data->shared_data->philo_number == 0)
		return (data->err_num = 4, 1);
	data->shared_data->time_to_die = ft_atoi(args[2]) * 1000;
	data->shared_data->time_to_eat = ft_atoi(args[3]) * 1000;
	data->shared_data->time_to_sleep = ft_atoi(args[4]) * 1000;
	if (args[5])
	{
		data->meals_per_philo = ft_atoi(args[5]);
		if (data->meals_per_philo <= 0)
			return (data->err_num = 3, 1);
	}
	else
		data->meals_per_philo = -1;
	return (0);
}

bool	mutex_init(pthread_mutex_t *mtx)
{
	int	s;

	s = pthread_mutex_init(mtx, NULL);
	if (s != 0)
		return (false);
	return (true);
}

int	initializ_locks(t_data *data)
{
	size_t	i;

	i = 0;
	if (!mutex_init(&data->shared_data->print_mtx))
		return (data->err_num = 5, 1);
	if (!mutex_init(&data->shared_data->stop_mtx))
		return (data->err_num = 5, 1);
	if (!mutex_init(&data->shared_data->meal_count_mtx))
		return (data->err_num = 5, 1);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->shared_data->philo_number);
	if (!data->forks)
		return (data->err_num = 8, 1);
	while (i < data->shared_data->philo_number)
	{
		if (!mutex_init(&data->forks[i++]))
			return (data->err_num = 5, 1);
	}
	return (0);
}

int	init_philo(t_data *p_data, int i)
{
	int	s;
	int	p_nb;

	p_data->philos[i].meals = 0;
	p_data->philos[i].index = i + 1;
	p_data->philos[i].shared_data = p_data->shared_data;
	p_data->philos[i].last_meal_time = get_time_ms();
	p_data->philos[i].left_forks = &p_data->forks[i];
	if (!mutex_init(&p_data->philos[i].meal_mtx))
		return (p_data->err_num = 5, 1);
	p_nb = p_data->shared_data->philo_number;
	if (p_nb != 1)
	{
		if (i == 0)
			p_data->philos[i].right_fork = &p_data->forks[p_nb - 1];
		else
			p_data->philos[i].right_fork = &p_data->forks[i - 1];
	}
	s = pthread_create(&(p_data->philos[i].id), NULL, philo,
			&p_data->philos[i]);
	if (s != 0)
		return (p_data->err_num = 6, 1);
	return (0);
}
