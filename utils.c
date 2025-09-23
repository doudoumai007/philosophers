#include "philosopher.h"

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