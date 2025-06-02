/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:45:02 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 13:28:31 by mpapin           ###   ########.fr       */
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

	data->time_start = timestamp();
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_to_eat = 0;
		data->philo[i].fork_right = NULL;
		data->philo[i].info = data;
		data->philo[i].nb_meal = 0;
		pthread_mutex_init(&(data->philo[i].fork_left), NULL);
		if (i == data->n_philo - 1)
			data->philo[i].fork_right = &data->philo[0].fork_left;
		else
			data->philo[i].fork_right = &data->philo[i + 1].fork_left;
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->n_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	check_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
/*
	data->philo[i].fork_left = malloc(sizeof(pthread_mutex_t));
	Une fourchette/philosophe

	pthread_mutex_init(&data->print, NULL);
	Sortie protect par un mutex

	pthread_mutex_init(&data->m_dead, NULL);
	Empeche la mort instante et portect de manger en meme temps
*/

int	var_init(t_info *data, char **av)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	data->stop = 0;
	if (check_num(av))
		return (printf("Invalid Arguments\n"), 1);
	data->n_philo = ft_atoi(av[1]);
	if (data->n_philo <= 0)
		return (1);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->nb_to_eat = -1;
	if (av[5])
		data->nb_to_eat = ft_atoi(av[5]);
	else
		data->nb_to_eat = -1;
	if (av[5] && data->nb_to_eat == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (printf("Memory allocation failed\n"), 2);
	data->philo_eat = 0;
	return (0);
}
