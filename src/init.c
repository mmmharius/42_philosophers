/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:07 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:59:07 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_all(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error\nUsage : ./philo ");
		return (printf("nb_philos t_die t_eat t_sleep [must_eat]\n"));
	}
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->stop = false;
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->philos || !data->forks)
		return (cleanup(data), 1);
	pthread_mutex_init(&data->print_lock, NULL);
	i = 0;
	while (i < data->nb_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	return (init_philosophers(data));
}
