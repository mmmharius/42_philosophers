/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:37:30 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:37:30 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Point d'entrée du programme
// Initialise les données et les threads
// Lance le moniteur et attend la fin
// Libère les ressources avant de quitter
int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (init_all(&data, argc, argv) != 0)
		return (1);
	data.start_time = get_time();
	i = 0;
	while (i < data.nb_philos)
	{
		pthread_create(&data.philos[i].thread,
			NULL, philo_routine, &data.philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, &data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data.nb_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	cleanup(&data);
	return (0);
}
