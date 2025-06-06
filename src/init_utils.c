/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:45:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 21:44:23 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	data->start_time = get_current_time();
	if (data->nb_meals == 0)
		return ;
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal_time = get_current_time();
		pthread_create(&data->philos[i].thread, NULL,
			&philo_thread, &data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_thread, data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->forks);
	free(data->philos);
}
