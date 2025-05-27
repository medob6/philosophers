/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:53:48 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/27 13:49:05 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

# define SEM_FORKS "/forks_sem"

typedef struct philo_s
{
	pid_t		id;
	int			exit_status;
	t_data		*data;

}				t_philo;

typedef struct data_s
{
	sem_t		*forks;
	size_t		time_to_eat;
	size_t		time_to_die;
	size_t		time_to_sleep;
	size_t		philo_number;
	int			meals_per_philo;
	pthread_t	monitor_id;
	bool		monitor_created;
	t_philo		*philos;
	bool		simulation_stopped;

}				t_data;

void			errExitEN(t_data *data, int err_num);
void			get_data(t_data *data, char **args);
int				monitor_philos(t_data *data);
void			wait_monitor(t_data *data);
int				wait_philos(t_data *data);
void			check_args(int ac, char **av);

// utils librarys :
// void	ft_sleep(size_t time, t_philo *philo);
int				ft_isdigit(int c);
int				ft_atoi(char *str);
size_t			ft_strlen(const char *s);
void			cleanup(t_data *data);

#endif