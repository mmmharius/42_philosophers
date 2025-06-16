/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:50:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/16 18:14:43 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, long long time_to_die)
{
	long long	last_meal;
	long long	current_time;

	pthread_mutex_lock(&philo->data->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_lock);
	current_time = get_current_time();
	if (current_time - last_meal >= time_to_die)
		return (1);
	return (0);
}

int	check_if_all_ate(t_data *data)
{
	int	finished_eating;

	finished_eating = 0;
	if (data->nb_meals == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	if (data->finished_eating == data->nb_philos)
		finished_eating = 1;
	pthread_mutex_unlock(&data->meal_lock);
	return (finished_eating);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (philosopher_dead(&data->philos[i], data->time_to_die))
		{
			pthread_mutex_lock(&data->dead_lock);
			if (!data->dead)
			{
				data->dead = 1;
				pthread_mutex_lock(&data->write_lock);
				printf("%lld %d died\n",
					get_current_time() - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->write_lock);
			}
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_if_dead(data) || check_if_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}
