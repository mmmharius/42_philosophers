/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:20:52 by mpapin            #+#    #+#             */
/*   Updated: 2025/05/30 15:49:11 by mpapin           ###   ########.fr       */
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
	nb_eat		= nb repas manger
	is_eating	= bool quand mange
	last_eat	= temps depuis last repas
	id 			= id du philo
	thread		= thread di philo
*/

typedef struct s_philo
{
	int				nb_eat;
	bool			is_eating;
	long int		last_eat;
	int				id;
	pthread_t		thread;
	struct s_info	*info;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	fork_left;
}	t_philo;

/*
	philo_nbeat		= total repas consomme
	nb_philo		= nb total de philo
	t_to_die		= temps avant meurt de faim
	t_to_eat		= temps qui met a manger
	t_to_sleep		= temps de repos
	nb_meal			= nb de repas avant fin
	stop			= bool en cours/fin
	t_start			= timestamp du debut de la simu
	*philo			= tableau de philos
	print			= mutex pour les print
	stop			= mutex pour l'arret de la simu
	eat				= mutex pour l'acces aux repas
	dead			= mutex piur la mort
*/
typedef struct s_info
{
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				philo_nbeat;
	int				nb_philo;
	int				nb_meal;
	int				t_stop;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	stop;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}	t_info;

// utils/utils.c
int			ft_atoi(const char *str);
int			ft_isdigit(int character);
int			check_arg(char **str);
void		ft_usleep(int ms);

// src/init.c
int			philo_init(t_info *data);
int			var_init(t_info *data, char **av);

// src/philo.c


// src/utils.c
void		print(t_philo *philo, char *str);
long long	timestamp(void);
void		*philo_life(void *philo);
// void		*philo_life(void *phi);
int			is_dead(t_philo *philo, int nb);

#endif
