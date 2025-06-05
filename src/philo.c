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

void	*check_death(void *phi)
{
	t_philo	*philo;
	long	last_meal;

	philo = (t_philo *)phi;
	while (!is_dead(philo, 0))
	{
		pthread_mutex_lock(&philo->info->m_eat);
		last_meal = philo->last_to_eat;
		pthread_mutex_unlock(&philo->info->m_eat);
		if (timestamp() - last_meal >= (long)(philo->info->t_to_die))
		{
			print(philo, " died\n");
			is_dead(philo, 1);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->m_dead);
	if (nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_dead);
	return (0);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->info->n_philo == 1)
	{
		pthread_mutex_lock(&(philo->fork_left));
		print(philo, " has taken a fork\n");
		ft_usleep(philo->info->t_to_die * 2);
		pthread_mutex_unlock(&(philo->fork_left));
		return (0);
	}
	if (&(philo->fork_left) < philo->fork_right)
	{
		first = &(philo->fork_left);
		second = philo->fork_right;
	}
	else
	{
		first = philo->fork_right;
		second = &(philo->fork_left);
	}
	pthread_mutex_lock(first);
	print(philo, " has taken a fork\n");
	pthread_mutex_lock(second);
	print(philo, " has taken a fork\n");
	return (1);
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_to_eat = timestamp();
	philo->nb_meal++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->t_to_eat);
	if (&(philo->fork_left) < philo->fork_right)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(&(philo->fork_left));
	}
	else
	{
		pthread_mutex_unlock(&(philo->fork_left));
		pthread_mutex_unlock(philo->fork_right);
	}
	if (!is_dead(philo, 0))
	{
		print(philo, " is sleeping\n");
		ft_usleep(philo->info->t_to_sleep);
		print(philo, " is thinking\n");
	}
}

void	*philo_life(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->t_to_eat / 10);
	while (!is_dead(philo, 0))
	{
		if (take_fork(philo))
			philo_eat(philo);
		else
			break ;
		if (philo->info->nb_to_eat != -1 && philo->nb_meal == philo->info->nb_to_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				is_dead(philo, 1);
			}
			else
				pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}
