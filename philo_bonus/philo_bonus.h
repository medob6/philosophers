/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:53:48 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/29 18:28:52 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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
# define SEM_WRITE "/write_sem"

struct data_s; // forward declaration

typedef struct philo_s
{
	pid_t			id;
	size_t			index;
	int				exit_status;
	struct data_s	*data;
	time_t			last_meal_time;
	int				meals;
	int				status;
	bool			simulation_stop;
}					t_philo;

typedef struct data_s
{
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*death_lock;
	size_t			time_to_eat;
	time_t			time_to_die;
	size_t			time_to_sleep;
	size_t			philo_number;
	int				meals_per_philo;
	pthread_t		monitor_id;
	bool			monitor_created;
	t_philo			*philos;
	bool			simulation_stopped;
	time_t			start_date;
	sem_t			*sem_stop;
}					t_data;

// Core functions
void				errExitEN(t_data *data, int err_num);
void				get_data(t_data *data, char **args);
void				check_args(int ac, char **av);
int					wait_philos(t_data *data);
void				cleanup(t_data *data);
void				init_locks(t_data *data);
void				destroy_locks(t_data *data);

// Time + print utils
time_t				get_time_ms(void);
void				print_philo_state(const char *state, t_philo *philo);

// Philo actions
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				philo_eat(t_philo *philo);

// Utils
int					ft_isdigit(int c);
int					ft_atoi(char *str);
size_t				ft_strlen(const char *s);

#endif
