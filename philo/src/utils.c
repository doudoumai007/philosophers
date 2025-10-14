/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:12:50 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/14 19:13:55 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_dead(t_data *d)
{
	pthread_mutex_lock(&d->dead_lock);
	if (d->dead)
	{
		pthread_mutex_unlock(&d->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&d->dead_lock);
	return (0);
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < ms)
		usleep(100);
}

void	print_state(int id, t_data *d, char *msg)
{
	long long	time;

	pthread_mutex_lock(&d->print_lock);
	if (!d->dead)
	{
		time = get_timestamp() - d->start_time;
		printf("%lld %d %s\n", time, id, msg);
	}
	pthread_mutex_unlock(&d->print_lock);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nbr;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}
