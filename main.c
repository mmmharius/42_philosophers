/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:31:06 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 21:41:38 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	init_forks(data);
	init_philosophers(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: bad arguments\n"), 1);
	if (check_valid_args(argv))
		return (printf("Error: invalid arguments\n"), 1);
	if (init_data(&data, argv))
		return (printf("Error: init data failed\n"), 1);
	if (init_philos(&data))
		return (printf("Error: init philos failed\n"), 1);
	start_dinner(&data);
	destroy_all(&data);
	return (0);
}
