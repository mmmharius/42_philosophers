/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:44:56 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/26 14:47:21 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_to_die + 1);
	pthread_mutex_lock(&philo->info->eat);
	pthread_mutex_lock(&philo->info->stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->info->t_to_die))
	{
		pthread_mutex_unlock(&philo->info->eat);
		pthread_mutex_unlock(&philo->info->stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->eat);
	pthread_mutex_unlock(&philo->info->stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_left));
	print(philo, " has taken a fork\n");
	if (philo->info->nb_philo == 1)
	{
		ft_usleep(philo->info->t_to_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_right));
	print(philo, " has taken a fork\n");
}

void	philo_nbeat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->eat));
	philo->last_eat = timestamp();
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->info->eat));
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
		philo_nbeat(philo);
		if (philo->nb_eat == philo->info->nb_meal)
		{
			pthread_mutex_lock(&philo->info->stop);
			if (++philo->info->philo_nbeat == philo->info->nb_philo)
				is_dead(philo, 2);
			pthread_mutex_unlock(&philo->info->stop);
			return (NULL);
		}
	}
	return (NULL);
}
