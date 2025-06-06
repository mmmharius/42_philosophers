/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:56 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 20:58:47 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	if (philo->data->nb_philos == 1)
	{
		my_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	dream(t_philo *philo)
{
	print_status(philo, "is sleeping");
	my_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(1);
	while (!dead_loop(philo->data))
	{
		eat(philo);
		if (philo->data->nb_meals != -1 
			&& philo->meals_eaten >= philo->data->nb_meals)
		{
			pthread_mutex_lock(&philo->data->meal_lock);
			philo->data->finished_eating++;
			pthread_mutex_unlock(&philo->data->meal_lock);
			break ;
		}
		dream(philo);
		think(philo);
	}
	return (NULL);
}

int	philosopher_dead(t_philo *philo, long long time_to_die)
{
	long long	last_meal;
	long long	current_time;

	pthread_mutex_lock(&philo->data->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_lock);
	current_time = get_current_time();
	if (current_time - last_meal >= time_to_die)
		return (1);
	return (0);
}

int	check_if_all_ate(t_data *data)
{
	int	finished_eating;

	finished_eating = 0;
	if (data->nb_meals == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	if (data->finished_eating == data->nb_philos)
		finished_eating = 1;
	pthread_mutex_unlock(&data->meal_lock);
	return (finished_eating);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (philosopher_dead(&data->philos[i], data->time_to_die))
		{
			print_status(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_if_dead(data) || check_if_all_ate(data))
			break ;
		usleep(100);
	}
	return (NULL);
}