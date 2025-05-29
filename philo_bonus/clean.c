/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:27:50 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 18:28:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_locks(t_data *data)
{
	if (!data->forks)
		return ;
	sem_close(data->forks);
	sem_close(data->death_lock);
	sem_close(data->write_lock);
	sem_close(data->sem_stop);
	sem_unlink("/death_lock");
	sem_unlink(SEM_FORKS);
	sem_unlink("/write_lock");
	sem_unlink("/sim_lock");
	data->forks = NULL;
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	destroy_locks(data);
	free(data->philos);
	free(data);
}
