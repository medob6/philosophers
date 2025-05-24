/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:32:04 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/24 18:59:23 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_stopped(t_philo *philo)
{
	bool	stop;

	pthread_mutex_lock(&philo->shared_data->stop_mtx);
	stop = philo->shared_data->simulation_stopped;
	pthread_mutex_unlock(&philo->shared_data->stop_mtx);
	return (stop);
}

void	print_philo_state(const char *state, t_philo *philo)
{
	time_t	timestamp;

	pthread_mutex_lock(&philo->shared_data->stop_mtx);
	if (philo->shared_data->simulation_stopped)
	{
		pthread_mutex_unlock(&philo->shared_data->stop_mtx);
		return ;
	}
	pthread_mutex_lock(&philo->shared_data->print_mtx);
	timestamp = get_time_ms() - philo->shared_data->start_date;
	printf("%zu %zu %s\n", timestamp, philo->index, state);
	pthread_mutex_unlock(&philo->shared_data->print_mtx);
	pthread_mutex_unlock(&philo->shared_data->stop_mtx);
}

void	*handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_forks);
	print_philo_state("taken a fork", philo);
	ft_sleep(philo->shared_data->time_to_die, philo);
	pthread_mutex_unlock(philo->left_forks);
	return (NULL);
}

void	*philo(void *philo_data)
{
	t_philo	*philo;

	philo = (t_philo *)philo_data;
	if (philo->shared_data->philo_number == 1)
		return (handle_single_philo(philo));
	while (!simulation_stopped(philo))
	{
		lock_forks(philo->left_forks, philo->right_fork, philo->index);
		print_philo_state("taken a fork", philo);
		print_philo_state("is eating", philo);
		pthread_mutex_lock(&philo->meal_mtx);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&philo->meal_mtx);
		ft_sleep(philo->shared_data->time_to_eat, philo);
		unlock_forks(philo->left_forks, philo->right_fork, philo->index);
		pthread_mutex_lock(&philo->meal_mtx);
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mtx);
		print_philo_state("is sleeping", philo);
		ft_sleep(philo->shared_data->time_to_sleep, philo);
		print_philo_state("is thinking", philo);
		// ft_sleep(calc_think_time(philo) * 700, philo);
		usleep(500);
	}
	return (NULL);
}

int	creat_philos(t_data *p_data)
{
	size_t	i;

	i = 0;
	p_data->philos = malloc(sizeof(t_philo)
			* p_data->shared_data->philo_number);
	if (!p_data->philos)
		return (p_data->err_num = 8, 1);
	while (i < p_data->shared_data->philo_number)
	{
		if (init_philo(p_data, i++))
			return (1);
	}
	return (0);
}
