/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:31:06 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 13:21:06 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_philo(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_left);
		pthread_mutex_destroy(data->philo[i].fork_right);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_dead);
}

int	main(int ac, char **av)
{
	t_info	data;

	data.philo = NULL;
	if (ac != 5 && ac != 6)
		return (0);
	if (var_init(&data, av) == 1)
	{
		free(data.philo);
		return (0);
	}
	philo_init(&data);
	clear_philo(&data);
}
