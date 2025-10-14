/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:57:45 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 19:38:21 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	cleanup_threads(t_data *d, int created)
{
	int	i;

	i = 0;
	while (i < created)
		pthread_join(d->philos[i++].thread, NULL);
}

void	cleanup_on_error(t_data *d, int stage)
{
	int	i;

	if (stage >= 2)
	{
		i = 0;
		while (i < d->nb_philo)
			pthread_mutex_destroy(&d->forks[i++]);
		pthread_mutex_destroy(&d->dead_lock);
		pthread_mutex_destroy(&d->print_lock);
	}
	if (stage >= 1)
	{
		free(d->forks);
		free(d->philos);
	}
}
