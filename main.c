/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:31:06 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/22 22:31:54 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_left);
		pthread_mutex_destroy(data->philo[i].fork_right);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
}

int	main(int argc, char **argv)
{
	t_info	data;

	data.philo = NULL;
	if (argc != 5 && argc != 6)
		return (0);
	if (var_init(&data, argv) == 1)
	{
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	clear_philo(&data);
}
