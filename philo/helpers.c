/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:21:36 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 15:14:45 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	calc_think_time(t_philo *philo)
{
	time_t	think_time;

	think_time = philo->shared_data->time_to_die / 1000 - (get_time_ms() - philo->last_meal_time);
	return (think_time);
}

void	lock_forks(pthread_mutex_t *l_fork, pthread_mutex_t *r_fork,
		size_t philo_nbr)
{
	if (philo_nbr % 2 == 0)
	{
		pthread_mutex_lock(r_fork);
		pthread_mutex_lock(l_fork);
	}
	else
	{
		pthread_mutex_lock(l_fork);
		pthread_mutex_lock(r_fork);
	}
}

void	unlock_forks(pthread_mutex_t *l_fork, pthread_mutex_t *r_fork,
		size_t philo_nbr)
{
	if (philo_nbr % 2 == 0)
	{
		pthread_mutex_unlock(r_fork);
		pthread_mutex_unlock(l_fork);
	}
	else
	{
		pthread_mutex_unlock(l_fork);
		pthread_mutex_unlock(r_fork);
	}
}

time_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_philo_meals(t_data *data, size_t i)
{
	int	meals;

	pthread_mutex_lock(&data->philos[i].meal_mtx);
	meals = data->philos[i].meals;
	pthread_mutex_unlock(&data->philos[i].meal_mtx);
	return (meals);
}
