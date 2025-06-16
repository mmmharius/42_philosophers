/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/16 18:14:42 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dream(t_philo *philo)
{
	print_status(philo, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	long long	think_time;

	print_status(philo, "is thinking");
	if (philo->data->nb_philos % 2 == 1)
	{
		think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
		if (think_time < 0)
			think_time = 0;
		if (think_time > 600)
			think_time = 200;
		my_usleep(think_time);
	}
}
