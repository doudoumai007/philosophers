#include "philosopher.h"

int parse_args_and_initial_d(int ac, char *av[], t_data *d)
{
	d->nb_philo = atoi(av[1]);
	d->time_to_die = atoi(av[2]);
	d->time_to_eat = atoi(av[3]);
	d->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		d->must_eat = atoi(av[5]);
	else
		d->must_eat = -1;
	if (d->nb_philo <= 0 || d->time_to_die <= 0 || d->time_to_eat <= 0 || d->time_to_sleep <= 0)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nb_philo);
	if (!d->forks)
	{
		printf("Error: malloc forks failed\n");
		return (1);
	}
	d->philos = malloc(sizeof(t_philo) *d->nb_philo);
	if (!d->philos)
	{
		printf("Error: malloc philo failed\n");
		return (1);
	}
	int	i = 0;
	while (i < d->nb_philo)
	{
		pthread_mutex_init(&d->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&d->dead_lock, NULL);
	pthread_mutex_init(&d->print_lock, NULL);
	d->dead = 0;
	d->start_time = get_timestamp();
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*d;

	philo = (t_philo *)arg;
	d = philo->d;
	while (!d->dead)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

void	initial_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philo)
	{
		d->philos[i].id = i + 1;
		d->philos[i].meals_eaten = 0;
		d->philos[i].last_meal = d->start_time;
		d->philos[i].d = d;
		pthread_create(&d->philos[i].thread, NULL, routine, &d->philos[i]);
		i++;
	}
}

int main(int ac, char *av[])
{
	t_data		d;
	pthread_t	monitor_thread;

	int		i;

	if (ac != 6)
	{
		printf("Usage: ./philo nb_philo time_to_die time_to_eat time_to_sleep [must_eat]\n");
		return (1);
	}
	if (parse_args_and_initial_d(ac, av, &d))
		return (1);
	initial_philo(&d);
	i = 0;
	while (i < d.nb_philo)
	{
		pthread_join(d.philos[i].thread, NULL);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, d.philos);
	pthread_join(monitor_thread, NULL);
	return (0);
	}
