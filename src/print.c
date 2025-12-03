/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:06:09 by peiyli            #+#    #+#             */
/*   Updated: 2025/12/01 12:59:29 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_state(int id, t_data *d, char *msg)
{
	long long	time;
	int			if_dead;

	if_dead = is_dead(d);
	pthread_mutex_lock(&d->print_lock);
	if (!if_dead || ft_strncmp(msg, "died", 4) == 0)
	{
		time = get_timestamp() - d->start_time;
		printf("%lld %d %s\n", time, id, msg);
	}
	pthread_mutex_unlock(&d->print_lock);
}
