/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:31:47 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/25 14:46:50 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_data *data)
{
	size_t	i;

	if (!data->forks)
		return ;
	i = 0;
	while (i < data->shared_data->philo_number)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	destroy_philos(t_data *data)
{
	size_t	i;

	if (!data->philos)
		return ;
	i = 0;
	while (i < data->shared_data->philo_number)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mtx);
		i++;
	}
	free(data->philos);
}

void	destroy_shared_data(t_shared_data *shared)
{
	if (!shared)
		return ;
	pthread_mutex_destroy(&shared->print_mtx);
	pthread_mutex_destroy(&shared->stop_mtx);
	pthread_mutex_destroy(&shared->meal_count_mtx);
	free(shared);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	destroy_forks(data);
	destroy_philos(data);
	destroy_shared_data(data->shared_data);
	free(data);
}
