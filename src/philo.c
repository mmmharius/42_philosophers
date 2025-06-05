/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:56 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 13:35:40 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_stopped(t_info *info)
{
	pthread_mutex_lock(&info->m_dead);
	if (info->stop)
	{
		pthread_mutex_unlock(&info->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&info->m_dead);
	return (0);
}

void	stop_simulation(t_info *info)
{
	pthread_mutex_lock(&info->m_dead);
	info->stop = 1;
	pthread_mutex_unlock(&info->m_dead);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (simulation_stopped(philo->info))
		return (0);
	if (philo->info->n_philo == 1)
	{
		pthread_mutex_lock(philo->fork_left);
		print(philo, " has taken a fork\n");
		ft_usleep(philo->info->t_to_die + 1);
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	if (philo->fork_left < philo->fork_right)
	{
		first = philo->fork_left;
		second = philo->fork_right;
	}
	else
	{
		first = philo->fork_right;
		second = philo->fork_left;
	}
	pthread_mutex_lock(first);
	if (simulation_stopped(philo->info))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	print(philo, " has taken a fork\n");
	pthread_mutex_lock(second);
	if (simulation_stopped(philo->info))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	print(philo, " has taken a fork\n");
	return (1);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_to_eat = timestamp();
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->info->m_eat);
	ft_usleep_check(philo->info->t_to_eat, philo->info);
	release_forks(philo);
}

void	*philo_life(void *phi)
{
	t_philo	*philo;
	int		took_forks;

	philo = (t_philo *)phi;
	if (philo->info->n_philo > 1)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->info->t_to_eat);
		else if (philo->info->n_philo % 2 == 1)
		{
			if (philo->id % 3 == 0)
				ft_usleep(philo->info->t_to_eat * 2);
		}
	}
	while (!simulation_stopped(philo->info))
	{
		took_forks = take_forks(philo);
		if (!took_forks)
			break ;
		philo_eat(philo);
		if (philo->info->nb_to_eat != -1 && philo->nb_meal >= philo->info->nb_to_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			philo->info->philo_eat++;
			if (philo->info->philo_eat == philo->info->n_philo)
				stop_simulation(philo->info);
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
		if (simulation_stopped(philo->info))
			break ;
		print(philo, " is sleeping\n");
		ft_usleep_check(philo->info->t_to_sleep, philo->info);
		if (simulation_stopped(philo->info))
			break ;
		print(philo, " is thinking\n");
	}
	return (NULL);
}