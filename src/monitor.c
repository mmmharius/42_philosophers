/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:11 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:59:11 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	all_philos_full(t_data *d)
{
	int	i;
	int	full_count;

	if (d->must_eat < 0)
		return (0);
	full_count = 0;
	i = 0;
	while (i < d->nb_philos)
	{
		if (d->philos[i].meals_eaten >= d->must_eat)
			full_count++;
		i++;
	}
	return (full_count == d->nb_philos);
}

void	*monitor_routine(void *arg)
{
	t_data	*d;
	int		i;
	long	timestamp;

	d = (t_data *)arg;
	while (!d->stop)
	{
		i = 0;
		while (i < d->nb_philos)
		{
			timestamp = get_time() - d->philos[i].last_meal;
			if (timestamp > d->time_to_die)
			{
				pthread_mutex_lock(&d->print_lock);
				printf("%ld.%03ldms", timestamp / 1000, timestamp % 1000);
				printf(" %d died\n", d->philos[i].id);
				d->stop = true;
				pthread_mutex_unlock(&d->print_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
