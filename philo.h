/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 08:51:59 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/24 10:03:45 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef struct shared_data_s
{
	pthread_mutex_t	print_mtx;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	pthread_mutex_t	meal_count_mtx;
	struct timeval	start_date;
	bool			philo_is_dead;
	bool			simulation_stopped;
	pthread_mutex_t	stop_mtx;
	size_t			philo_number;
}					t_shared_data;

typedef struct philo_s
{
	pthread_t		id;
	size_t			index;
	pthread_mutex_t	*left_forks;
	pthread_mutex_t	*right_fork;
	t_shared_data	*shared_data;
	int				meals;
	size_t			last_meal_time;
	pthread_mutex_t	meal_mtx;

}					t_philo;

typedef struct data_s
{
	pthread_t		monitor_id;
	pthread_mutex_t	*forks;
	t_shared_data	*shared_data;
	t_philo			*philos;
	int				meals_per_philo;
	int				err_num;

}					t_data;

void				print_err(const char *err, const char *color);
int					validate_args(char **av);
void				unvalid_args(int err_n);
bool				check_args(int ac, char **av);
int					get_data(t_data *data, char **args);
bool				mutex_init(pthread_mutex_t *mtx);
int					initializ_locks(t_data *data);
void				cleanup(t_data *data);
int					init_philo(t_data *p_data, int index);
int					creat_philos(t_data *p_data);
void				*monitor_thread(void *arg);
int					wait_monitor(t_data *data);
int					monitor_philos(t_data *data);
size_t				get_timestamp(struct timeval start);
void				print_philo_state(const char *state, t_philo *philo);
void				*philo(void *philo_data);
int					get_philo_meals(t_data *data, size_t i);
int					quit_in_err(t_data *data, int err_num);
void				ft_sleep(size_t time, t_philo *philo);
void				unlock_forks(pthread_mutex_t *l_fork,
						pthread_mutex_t *r_fork, size_t philo_nbr);
void				lock_forks(pthread_mutex_t *l_fork, pthread_mutex_t *r_fork,
						size_t philo_nbr);
bool				simulation_stopped(t_philo *philo);
// utils librarys :

int					ft_isdigit(int c);
int					ft_atoi(char *str);
size_t				ft_strlen(const char *s);
#endif