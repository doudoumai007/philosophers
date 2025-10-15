/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:47:12 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 19:55:33 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->forks[0]);
	print_state(philo->id, philo->d, "has taken a fork");
	while (!is_dead(philo->d))
		usleep(1000);
	pthread_mutex_unlock(&philo->d->forks[0]);
}
