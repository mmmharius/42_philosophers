/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:59:18 by mpapin            #+#    #+#             */
/*   Updated: 2025/04/15 14:59:18 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Retourne le temps actuel en millisecondes
// Utilise gettimeofday pour préciser l'heure
// Combine secondes et microsecondes
// Sert à mesurer les délais d'activité
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Attente active en millisecondes
// Utilise get_time pour chronométrer
// Effectue des pauses répétées
// Meilleure précision que sleep classique
void	usleep_custom(long time_in_ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
		usleep(500);
}

// Affiche l'état d'un philosophe
// Protège l'accès à l'affichage avec un mutex
// Affiche le temps, l'identifiant et l'état
// Ne rien afficher si la simulation est arrêtée
void	print_state(t_philo *p, char *msg)
{
	t_data	*d;

	d = p->data;
	pthread_mutex_lock(&d->print_lock);
	if (!d->stop)
		printf("%ld %d %s\n", get_time() - d->start_time, p->id, msg);
	pthread_mutex_unlock(&d->print_lock);
}

// Libère la mémoire allouée et détruit les mutex
// Appelée en cas d'erreur ou à la fin
// Nettoie les philosophes, les fourchettes et le mutex d'impression
void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_lock);
}
