/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:16 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 18:51:50 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)arg;
	d = philo->d;
	while (!is_dead(d))
	{
		think(philo);
		if (philo->d->nb_philo == 1)
		{
			handle_one_philo(philo);
			break ;
		}
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
