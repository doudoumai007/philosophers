#include "philosopher.h"

int	check_death(t_data *d)
{
	int		i;

    i = 0;
	while (i < d->nb_philo)
	{
		pthread_mutex_lock(&d->dead_lock);
		if (get_timestamp() - d->philos[i].last_meal > d->time_to_eat)
		{
			print_state(d->philos[i].id, d, "died");
			d->dead = 1;
			pthread_mutex_unlock(&d->dead_lock);
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

	if (d->must_eat < 0)
		return (0);
	i = 0;
	while (i < d->nb_philo)
	{
		if (d->philos[i].meals_eaten < d->must_eat)
			return (0);
		i++;
	}
	d->dead = 1;
	return (1);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)arg;
	d = philo[0].d;
	while (!d->dead)
	{
		if (check_death(d) || check_all_full(d))
			break ;
		usleep(1000);
	}
	return (NULL);
}