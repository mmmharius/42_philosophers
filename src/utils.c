/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:48 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 20:54:47 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_usleep(long long milliseconds)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->data->start_time;
	if (!dead_loop(philo->data))
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	dead_loop(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}