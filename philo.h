/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:20:52 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/02 13:37:50 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

/*
	n 				= Id philo
	nb_meal			= nb repas mange
	is_eating		= bool si mange
	thread			= thread associe au philo
	last_to_eat		= temps depuis dernier repas
	info			= lien vers t_info
	fork_right		= fourchette droite
	fork_left		= fourchette gauche
*/
typedef struct s_philo
{
	int				id;
	int				nb_meal;
	bool			is_eating;
	pthread_t		thread;
	long int		last_to_eat;
	struct s_info	*info;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

/*
	philo_eat		= total repas consomme
	n_philo			= nb total de philo
	t_to_die		= temps avant meurt de faim
	t_to_eat		= temps qui met a manger
	t_to_sleep		= temps de repos
	nb_to_eat		= nb de repas avant fin
	stop			= bool en cours/fin
	time_start		= timestamp du debut du prog
	*philo			= tableau de philos
	print			= mutex pour les printd
	m_stop			= mutex pour l'arret du prog
	m_eat			= mutex pour l'acces aux repas
	m_dead			= mutex pour la mort
*/
typedef struct s_info
{
	int				philo_eat;
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_to_eat;
	volatile int	stop;
	long int		time_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}	t_info;

void		ft_usleep(int ms);
void		ft_usleep_check(int ms, t_info *info);
int			philo_init(t_info *data);
long long	timestamp(void);
int			var_init(t_info *data, char **av);
void		*philo_life(void *phi);
void		print(t_philo *philo, char *str);
int			simulation_stopped(t_info *info);
void		stop_simulation(t_info *info);
int			take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
int			ft_isdigit(int character);
int			ft_atoi(const char *str);

#endif
