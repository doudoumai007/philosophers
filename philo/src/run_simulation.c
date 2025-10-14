/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:09:16 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 15:11:44 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)arg;
	d = philo->d;
	while (1)
	{
		if (is_dead(d))
			break ;
		think(philo);
		take_forks(philo);
		if (is_dead(d))
			break ;
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
