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
	philo->last_meal = get_timestamp();
    print_state(philo->id, philo->d, "is eating");
	ft_usleep(philo->d->time_to_eat);
	philo->meals_eaten++;
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