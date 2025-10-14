/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:08:24 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 19:31:12 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	initial_args(int ac, char *av[], t_data *d)
{
	d->nb_philo = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->must_eat = ft_atoi(av[5]);
	else
		d->must_eat = -1;
	if (d->nb_philo <= 0 || d->time_to_die <= 0
		|| d->time_to_eat <= 0 || d->time_to_sleep <= 0)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	return (0);
}

int	initial_mutexes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philo)
	{
		if (pthread_mutex_init(&d->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&d->dead_lock, NULL)
		|| pthread_mutex_init(&d->print_lock, NULL))
		return (printf("Error: global mutex init failed\n"), 1);
	return (0);
}

int	parse_args_and_initial_d(int ac, char *av[], t_data *d)
{
	if (initial_args(ac, av, d))
		return (1);
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb_philo);
	if (!d->forks)
		return (printf("Error: malloc forks failed\n"), 1);
	d->philos = malloc(sizeof(t_philo) * d->nb_philo);
	if (!d->philos)
	{
		free(d->forks);
		return (printf("Error: malloc philo failed\n"), 1);
	}
	if (initial_mutexes(d))
	{
		cleanup_on_error(d, 1);
		return (1);
	}
	d->dead = 0;
	d->start_time = get_timestamp();
	return (0);
}

int	check_args(int ac, char *av[], t_data *d)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: args numbers not corret");
		return (1);
	}
	if (parse_args_and_initial_d(ac, av, d))
		return (1);
	return (0);
}

int	initial_philo(t_data *d)
{
	int	i;

	d->start_time = get_timestamp();
	i = 0;
	while (i < d->nb_philo)
	{
		d->philos[i].id = i + 1;
		d->philos[i].meals_eaten = 0;
		d->philos[i].last_meal = d->start_time;
		d->philos[i].d = d;
		i++;
	}
	i = 0;
	while (i < d->nb_philo)
	{
		if (pthread_create(&d->philos[i].thread, NULL, routine, &d->philos[i]))
		{
			printf("Error: phread_create failed\n");
			cleanup_threads(d, i);
			return (1);
		}
		i++;
	}
	return (0);
}
