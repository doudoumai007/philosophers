/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:05:02 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 18:39:38 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char *av[])
{
	int			i;
	t_data		d;
	pthread_t	monitor_thread;

	if (check_args(ac, av, &d))
		return (1);
	if (initial_philo(&d))
	{
		cleanup_on_error(&d, 2);
		return (1);
	}
	pthread_create(&monitor_thread, NULL, monitor, &d);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < d.nb_philo)
		pthread_join(d.philos[i++].thread, NULL);
	cleanup_on_error(&d, 2);
	return (0);
}
