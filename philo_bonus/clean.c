/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:27:50 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/26 19:03:49 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_forks(t_data *data)
{
	if (!data->forks)
		return ;
	sem_close(data->forks);
	sem_unlink(SEM_FORKS);
	data->forks = NULL;
}

// void	destroy_philos(t_data *data)
// {
// 	size_t	i;

// 	if (!data->philos)
// 		return ;
// 	i = 0;
// 	while (i < data->shared_data->philo_number)
// 	{
// 		pthread_mutex_destroy(&data->philos[i].meal_mtx);
// 		i++;
// 	}
// 	free(data->philos);
// }

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	destroy_forks(data);
	// destroy_philos(data);
	free(data);
}
