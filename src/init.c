/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:45:02 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/30 17:18:50 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0) un philosophe un thread

	pthread_mutex_init(&(data->philo[i].fork_left), NULL); fourchette -> mutex
*/

int	philo_init(t_info *data)
{
	int	i;
	int	created_threads;

	data->t_start = timestamp();
	created_threads = 0;
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].nb_eat = 0;
		data->philo[i].info = data;
		pthread_mutex_init(&(data->philo[i].fork_left), NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].fork_right = &data->philo[0].fork_left;
		else
			data->philo[i].fork_right = &data->philo[i + 1].fork_left;
		if (pthread_create(&data->philo[i].thread, NULL,
				&philo_life, &data->philo[i]) != 0)
			break ;
		created_threads++;
	}
	i = -1;
	while (++i < created_threads)
		pthread_join(data->philo[i].thread, NULL);
	if (created_threads < data->nb_philo)
		return (-1);
	return (0);
}

int	var_init(t_info *data, char **argv)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->stop, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->t_stop = 0;
	if (check_arg(argv))
		return (printf("Invalid Arguments\n"), 1);
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo <= 0)
		return (1);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->nb_meal = -1;
	if (argv[5])
		data->nb_meal = ft_atoi(argv[5]);
	if (argv[5] && data->nb_meal == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (printf("Memory allocation failed\n"), 2);
	data->philo_nbeat = 0;
	return (0);
}
