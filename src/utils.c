/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:18 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:59:18 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_custom(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
}

void	print_state(t_philo *p, char *msg)
{
	t_data	*d;
	long	timestamp;

	d = p->data;
	pthread_mutex_lock(&d->print_lock);
	if (!d->stop)
	{
		timestamp = get_time() - d->start_time;
		printf("%ld.%03ldms ", timestamp / 1000, timestamp % 1000);
		printf("%2d ", p->id);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&d->print_lock);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_lock);
}
