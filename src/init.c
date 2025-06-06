/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:45:02 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 20:58:54 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!is_digit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0 
		|| check_arg_content(argv[1]) == 1)
		return (1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (1);
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argv[5])
		data->nb_meals = ft_atoi(argv[5]);
	data->dead = 0;
	data->finished_eating = 0;
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	return (0);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
}

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

int	init_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	init_forks(data);
	init_philosophers(data);
	return (0);
}