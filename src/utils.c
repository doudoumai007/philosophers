/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:12:50 by peiyli            #+#    #+#             */
/*   Updated: 2025/12/01 12:58:00 by peiyli           ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nbr;

	j = 0;
	while (str[j])
	{
		if (str[j] < '0' && str[j] > '9')
			return (0);
		j++;
	}
	i = 0;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return (nbr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
