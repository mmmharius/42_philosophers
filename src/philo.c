/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:56 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 01:28:45 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_to_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_to_eat >= (long)(philo->info->t_to_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_left));
	print(philo, " has taken a fork\n");
	if (philo->info->n_philo == 1)
	{
		ft_usleep(philo->info->t_to_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_right));
	print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_to_eat = timestamp();
	philo->nb_meal++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->t_to_eat);
	pthread_mutex_unlock((philo->fork_right));
	pthread_mutex_unlock(&(philo->fork_left));
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->t_to_sleep);
	print(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	pthread_create(&t, NULL, check_death, phi);
	pthread_detach(t);
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->t_to_eat / 10);
	while (!is_dead(philo, 0))
	{
		take_fork(philo);
		philo_eat(philo);
		if (philo->nb_meal == philo->info->nb_to_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}