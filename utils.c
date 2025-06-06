/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:48 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 13:22:55 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	pthread_mutex_lock(&philo->info->m_dead);
	if (!philo->info->stop)
	{
		time = timestamp() - philo->info->time_start;
		if (time >= 0 && time <= INT_MAX)
			printf("%lld %d%s", timestamp() - philo->info->time_start,
				philo->id, str);
	}
	pthread_mutex_unlock(&philo->info->m_dead);
	pthread_mutex_unlock(&(philo->info->print));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	signe = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * signe);
}

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

void	ft_usleep(int ms)
{
	long int	time;
	long int	current;

	time = timestamp();
	current = time;
	while (current - time < ms)
	{
		usleep(1000);
		current = timestamp();
	}
}

void	ft_usleep_check(int ms, t_info *info)
{
	long int	time;
	long int	current;

	time = timestamp();
	current = time;
	while (current - time < ms && !simulation_stopped(info))
	{
		usleep(1000);
		current = timestamp();
	}
}
