/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:31:06 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/30 17:22:29 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->philo[i].fork_left);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_info	data;

	data.philo = NULL;
	if (argc != 5 && argc != 6)
		return (0);

	if (var_init(&data, argv) != 0)
	{
		if (data.philo)
			free(data.philo);
		return (0);
	}

	if (philo_init(&data) == -1)
	{
		clear_philo(&data);
		return (1);
	}

	clear_philo(&data);
	return (0);
}

