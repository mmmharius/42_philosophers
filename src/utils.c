/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:48 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/22 22:49:27 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->dead);
	if (nb)
		philo->info->t_stop = 1;
	if (philo->info->t_stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

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
	time = timestamp() - philo->info->t_start;
	if (!philo->info->t_stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lld %d%s\n", timestamp() - philo->info->t_start,
				 philo->id, str);
	pthread_mutex_unlock(&(philo->info->print));
}
