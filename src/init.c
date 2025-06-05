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

void	*supervisor(void *d)
{
	t_info	*data;
	int		i;
	long	last_meal;

	data = (t_info *)d;
	while (!simulation_stopped(data))
	{
		i = -1;
		while (++i < data->n_philo && !simulation_stopped(data))
		{
			pthread_mutex_lock(&data->m_eat);
			last_meal = data->philo[i].last_to_eat;
			pthread_mutex_unlock(&data->m_eat);
			if (timestamp() - last_meal >= (long)data->t_to_die)
			{
				print(&data->philo[i], " died\n");
				stop_simulation(data);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

int	init_forks_and_philos(t_info *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_to_eat = data->time_start;
		data->philo[i].info = data;
		data->philo[i].nb_meal = 0;
		data->philo[i].fork_left = &data->forks[i];
		data->philo[i].fork_right = &data->forks[(i + 1) % data->n_philo];
	}
	return (0);
}

int	philo_init(t_info *data)
{
	int			i;
	pthread_t	supervisor_thread;

	data->time_start = timestamp();
	if (init_forks_and_philos(data))
		return (1);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, 
				&philo_life, &(data->philo[i])) != 0)
			return (1);
	}
	pthread_create(&supervisor_thread, NULL, supervisor, data);
	pthread_join(supervisor_thread, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].thread, NULL);
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
	if (av[5] && data->nb_to_eat == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (printf("Memory allocation failed\n"), 2);
	data->philo_eat = 0;
	return (0);
}