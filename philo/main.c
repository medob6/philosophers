/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:42:09 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/26 16:59:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_philos(t_data *data)
{
	size_t	i;
	int		s;

	s = 0;
	i = 0;
	while (i < data->shared_data->philo_number)
	{
		if (data->philos[i].thread_created)
			s = pthread_join(data->philos[i].id, NULL);
		if (s != 0)
			return (data->err_num = 7, 1);
		i++;
	}
	return (0);
}

int	wait_monitor(t_data *data)
{
	int	s;

	s = 0;
	if (data->monitor_created)
		s = pthread_join(data->monitor_id, NULL);
	if (s != 0)
		return (data->err_num = 7, 1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (check_args(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (quit_in_err(data, 8));
	get_data(data, av);
	if (data->err_num)
		return (quit_in_err(data, data->err_num));
	initializ_locks(data);
	if (data->err_num)
		return (quit_in_err(data, data->err_num));
	creat_philos(data);
	if (data->err_num)
		return (quit_in_err(data, data->err_num));
	monitor_philos(data);
	if (data->err_num)
		return (quit_in_err(data, data->err_num));
	wait_philos(data);
	wait_monitor(data);
	if (data->err_num)
		return (quit_in_err(data, data->err_num));
	cleanup(data);
	return (0);
}

//TODO :  i should wait for all threads to becreated then start , to make them start at the same time
