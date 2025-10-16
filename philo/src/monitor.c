/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:12:37 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/16 12:26:17 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_data *d)
{
	int		i;

	i = 0;
	while (i < d->nb_philo)
	{
		pthread_mutex_lock(&d->dead_lock);
		if (get_timestamp() - d->philos[i].last_meal > d->time_to_die)
		{
			d->dead = 1;
			pthread_mutex_unlock(&d->dead_lock);
			print_state(d->philos[i].id, d, "died");
			return (1);
		}
		pthread_mutex_unlock(&d->dead_lock);
		i++;
	}
	return (0);
}

int	check_all_full(t_data *d)
{
	int	i;

	if (d->must_eat <= 0)
		return (0);
	i = 0;
	pthread_mutex_lock(&d->dead_lock);
	while (i < d->nb_philo)
	{
		if (d->philos[i].meals_eaten < d->must_eat)
		{
			pthread_mutex_unlock(&d->dead_lock);
			return (0);
		}
		i++;
	}
	d->dead = 1;
	pthread_mutex_unlock(&d->dead_lock);
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*d;

	d = (t_data *)arg;
	while (1)
	{
		if (check_death(d) || check_all_full(d))
		{
			// pthread_mutex_lock(&d->dead_lock);
			// d->dead = 1;
			// pthread_mutex_unlock(&d->dead_lock);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
