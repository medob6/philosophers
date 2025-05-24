/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:09:41 by mbousset          #+#    #+#             */
/*   Updated: 2025/05/24 10:15:29 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	long	res;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
			return (-sign * (sign == 1));
		res = res * 10 + ((str[i] - '0'));
		i++;
	}
	return ((int)res * sign);
}
size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(size_t duration, t_philo *philo)
{
	size_t	start;
	size_t	now;

	start = get_time_ms();
	while (true)
	{
		if (simulation_stopped(philo))
			break ;
		now = get_time_ms();
		if ((now - start) >= duration / 1000)
			break ;
		usleep(1000); // sleep in small chunks (1000 microseconds) = 1 mili sec
	}
}
