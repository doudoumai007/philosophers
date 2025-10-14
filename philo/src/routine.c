/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:12:45 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 19:31:38 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	think(t_philo *philo)
{
	print_state(philo->id, philo->d, "is thinking");
}

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->d->nb_philo;
	if (philo->d->nb_philo == 1)
	{
		handle_one_philo(philo);
		return ;
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->d->forks[right]);
		print_state(philo->id, philo->d, "has taken a fork");
		pthread_mutex_lock(&philo->d->forks[left]);
		print_state(philo->id, philo->d, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->d->forks[left]);
		print_state(philo->id, philo->d, "has taken a fork");
		pthread_mutex_lock(&philo->d->forks[right]);
		print_state(philo->id, philo->d, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	print_state(philo->id, philo->d, "is eating");
	pthread_mutex_lock(&philo->d->dead_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->d->dead_lock);
	ft_usleep(philo->d->time_to_eat);
}

void	put_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->d->nb_philo;
	pthread_mutex_unlock(&philo->d->forks[left]);
	pthread_mutex_unlock(&philo->d->forks[right]);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo->id, philo->d, "is sleeping");
	ft_usleep(philo->d->time_to_sleep);
}
