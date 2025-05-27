/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:46:43 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/26 18:54:59 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// bool	all_philos_met_target(t_data *data)
// {
// 	size_t	i;
// 	size_t	count;

// 	count = 0;
// 	i = 0;
// 	while (i < data->shared_data->philo_number)
// 	{
// 		if (get_philo_meals(data, i) >= data->meals_per_philo)
// 			count++;
// 		i++;
// 	}
// 	return (count == data->shared_data->philo_number);
// }

bool	all_meals_eaten(t_data *data)
{
    (void)data;
    // if (data->meals_per_philo != -1)
    // {
    // 	if (all_philos_met_target(data))
    // 	{
    // 		pthread_mutex_lock(&data->shared_data->stop_mtx);
    // 		data->shared_data->simulation_stopped = true;
    // 		pthread_mutex_unlock(&data->shared_data->stop_mtx);
    // 		return (true);
    // 	}
    // }
    return (false);
}

bool	philo_died(t_data *data, int i)
{
	// size_t	now;
	// size_t	last_meal;

	(void)i;
	(void)data;
	// pthread_mutex_lock(&data->philos[i].meal_mtx);
	// last_meal = data->philos[i].last_meal_time;
	// pthread_mutex_unlock(&data->philos[i].meal_mtx);
	// now = get_time_ms();
	// if ((now - last_meal) > data->shared_data->time_to_die / 1000)
	// {
	// 	pthread_mutex_lock(&data->shared_data->stop_mtx);
	// 	data->shared_data->simulation_stopped = true;
	// 	pthread_mutex_unlock(&data->shared_data->stop_mtx);
	// 	pthread_mutex_lock(&data->shared_data->print_mtx);
	// 	printf("%zu %d %s\n", now - data->shared_data->start_date, i + 1,
	// 		"died");
	// 	pthread_mutex_unlock(&data->shared_data->print_mtx);
	// 	return (true);
	// }
	return (false);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)arg;
	while (true)
	{
		if (data->simulation_stopped)
			break ;
		if (all_meals_eaten(data))
			return (NULL);
		i = 0;
		while (i < data->philo_number)
		{
			if (philo_died(data, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	monitor_philos(t_data *data)
{
	int s;

	s = pthread_create(&(data->monitor_id), NULL, monitor_thread, data);
	if (s != 0)
	{
		data->simulation_stopped = true;
		errExitEN(data, 6);
	}
	data->monitor_created = true;
	return (0);
}