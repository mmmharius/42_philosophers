/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:56 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/16 18:18:41 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	my_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat_take_forks(t_philo *philo)
{
	if (philo->id == philo->data->nb_philos)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	if (philo->data->nb_philos == 1)
	{
		eat_single_philo(philo);
		return ;
	}
	eat_take_forks(philo);
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

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(philo->data->time_to_eat / 2);
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

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
