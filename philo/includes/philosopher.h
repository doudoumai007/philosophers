/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:50 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 19:41:40 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

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
	pthread_mutex_t	*forks;
	// pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			meal;
	int			meals_eaten;
	long long	last_meal;
	t_data		*d;
	pthread_t	thread;
}	t_philo;

void		*routine(void *arg);

void		handle_one_philo(t_philo *philo);

int			initial_args(int ac, char *av[], t_data *d);
int			initial_mutexes(t_data *d);
int			parse_args_and_initial_d(int ac, char *av[], t_data *d);
int			check_args(int ac, char *av[], t_data *d);
int			initial_philo(t_data *d);

void		think(t_philo *philo);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		sleep_philo(t_philo *philo);

int			is_dead(t_data *d);
long long	get_timestamp(void);
void		ft_usleep(long long ms);
void		print_state(int id, t_data *d, char *msg);
int			ft_atoi(const char *str);

int			check_death(t_data *d);
int			check_all_full(t_data *d);
void		*monitor(void *arg);

void		cleanup_threads(t_data *d, int created);
void		cleanup_on_error(t_data *d, int stage);

#endif