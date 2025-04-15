/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:16 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:59:16 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Routine principale de chaque philosophe
// Pense, prend les fourchettes, mange puis dort
// S'arrête si la simulation est terminée
// Prend les fourchettes dans un ordre alterné
void	*philo_routine(void *arg)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)arg;
	d = p->data;
	if (p->id % 2 == 0)
		usleep_custom(5);
	while (!d->stop)
	{
		print_state(p, "is thinking");
		pthread_mutex_lock(p->left_fork);
		print_state(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_state(p, "has taken a fork");
		print_state(p, "is eating");
		p->last_meal = get_time();
		usleep_custom(d->time_to_eat);
		p->meals_eaten++;
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		print_state(p, "is sleeping");
		usleep_custom(d->time_to_sleep);
	}
	return (NULL);
}
