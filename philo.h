/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:20:52 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/06 20:55:29 by mpapin           ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				dead;
	int				finished_eating;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}	t_data;

long long	get_current_time(void);
void		my_usleep(long long milliseconds);
void		print_status(t_philo *philo, char *status);
int			dead_loop(t_data *data);
void		*philo_thread(void *arg);
void		*monitor_thread(void *arg);
void		eat_single_philo(t_philo *philo);
void		eat_take_forks(t_philo *philo);
void		dream(t_philo *philo);
void		think(t_philo *philo);
int			philosopher_dead(t_philo *philo, long long time_to_die);
int			check_if_all_ate(t_data *data);
int			check_if_dead(t_data *data);
int			init_data(t_data *data, char **argv);
int			init_philos(t_data *data);
void		start_dinner(t_data *data);
void		destroy_all(t_data *data);
void		init_forks(t_data *data);
void		init_philosophers(t_data *data);
int			ft_atoi(const char *str);
int			is_digit(char c);
int			check_valid_args(char **argv);
int			check_arg_content(char *arg);

#endif