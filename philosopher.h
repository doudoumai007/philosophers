#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
	pthread_mutex_t dead_lock;
} t_data;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal;
	t_data		*d;
	pthread_t	thread;
} t_philo;

int 		parse_args_and_initial_d(int ac, char *av[], t_data *d);
void		initial_philo(t_data *d);
void		*routine(void *arg);

void		think(t_philo *philo);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);

long long	get_timestamp(void);
void		ft_usleep(long long ms);
void		print_state(int id, t_data *d, char *msg);

int			check_death(t_data *d);
int			check_all_full(t_data *d);
void		*monitor(void *arg);

#endif