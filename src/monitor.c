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

// Surveille l'état des philosophes
// Vérifie s'ils sont morts de faim
// Arrête la simulation si un philosophe meurt
// Affiche l'événement et active le drapeau stop

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
				printf("%ld %d died\n",
					get_time() - d->start_time, d->philos[i].id);
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
