/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:54:56 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 19:00:52 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_state(const char *state, t_philo *philo)
{
	time_t	timestamp;

	sem_wait(philo->data->write_lock);
	timestamp = get_time_ms() - philo->data->start_date;
	printf("%zu %zu %s\n", timestamp, philo->index + 1, state);
	sem_post(philo->data->write_lock);
}

void	print_philo_state(const char *state, t_philo *philo)
{
	sem_wait(philo->data->death_lock);
	if (philo->simulation_stop)
	{
		sem_post(philo->data->death_lock);
		return ;
	}
	philo_state(state, philo);
	sem_post(philo->data->death_lock);
}

bool	philo_died(t_philo philo)
{
	time_t	now;

	now = get_time_ms();
	return ((now - philo.last_meal_time) > philo.data->time_to_die);
}

void	ft_sleep(int ms, t_philo *philo)
{
	time_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
	{
		if (philo_died(*philo) || philo->simulation_stop)
			break ;
		usleep(100);
	}
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	philo_state("taken a fork", philo);
	sem_wait(philo->data->forks);
	philo_state("taken a fork", philo);
	print_philo_state("is eating", philo);
	philo->last_meal_time = get_time_ms();
	ft_sleep(philo->data->time_to_eat, philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_state("is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_philo_state("is thinking", philo);
	usleep(500);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_died(*philo))
		{
			sem_wait(philo->data->death_lock);
			philo_state("died", philo);
			sem_wait(philo->data->write_lock);
			sem_wait(philo->data->sem_stop);
			philo->simulation_stop = true;
			sem_post(philo->data->sem_stop);
			destroy_locks(philo->data);
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

bool	simulation_stoped(t_philo *philo)
{
	sem_wait(philo->data->sem_stop);
	if (philo->simulation_stop)
	{
		sem_post(philo->data->sem_stop);
		return (true);
	}
	sem_post(philo->data->sem_stop);
	return (false);
}

void	philo(t_data *data, int i)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = &data->philos[i];
	philo->index = i;
	philo->meals = 0;
	philo->simulation_stop = false;
	philo->last_meal_time = get_time_ms();
	if (pthread_create(&monitor, NULL, death_monitor, philo) != 0)
	{
		print_philo_state("failed to create death monitor", philo);
		destroy_locks(philo->data);
		// TODO : wait for thread to finish pthred_join
		exit(EXIT_FAILURE);
	}
	while (!simulation_stoped(philo))
	{
		if (philo->data->meals_per_philo != -1
			&& philo->meals >= philo->data->meals_per_philo)
		{
			// TODO : wait for thread to finish pthred_join
			destroy_locks(philo->data);
			exit(0);
		}
		philo_eat(philo);
		philo->meals++;
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	creat_philo_prc(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		errExitEN(data, 6);
	else if (pid == 0)
		philo(data, i);
	else
	{
		data->philos[i].id = pid;
		data->philos[i].index = i + 1;
	}
}

int	creat_philos(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_number);
	if (!data->philos)
		errExitEN(data, 8);
	while (i < data->philo_number)
	{
		data->philos[i].data = data;
		creat_philo_prc(data, i++);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data *data;

	check_args(ac, av);
	data = malloc(sizeof(t_data));
	if (!data)
		errExitEN(data, 8);
	get_data(data, av);
	init_locks(data);
	creat_philos(data);
	wait_philos(data);
	cleanup(data);
	return (0);
}