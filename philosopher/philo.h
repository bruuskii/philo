/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 04:35:07 by izouine           #+#    #+#             */
/*   Updated: 2024/05/27 04:35:08 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ALL_PHILOS 201

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				philo_nbr;
	size_t			start_time;
	size_t			last_meal_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				meals_counter;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	int				nbr_of_meals;
	int				*dead;
	int				eating;
	int				meals_eaten;
}					t_philo;

typedef struct s_args
{
	size_t			philo_death_time;
	size_t			philo_sleep_time;
	size_t			philo_meal_time;
	int				philo_nbr;
	int				nbr_of_meals;
}					t_args;

typedef struct s_prog
{
	int				death_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;
}					t_prog;

int					init_args(t_args *args, int argc, char **argv);
int					exit_error(char *str);
int					ft_atoi(const char *s);
void				init_forks(pthread_mutex_t forks[], t_args *args);
int					init_philo(t_args *args, t_prog *prog,
						pthread_mutex_t *forks, t_philo *philo);
size_t				get_time(void);
void				*routine(void *arg);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
int					check_death(t_philo *philo);
void				print(t_philo *philo, char *s);
void				precise_usleep(size_t time);
void				prog_init(t_philo *philos, t_prog *prog);
void				*monitor(void *arg);
int					eat_times(t_philo *philo);
int					check_death(t_philo *philo);
int					init_threads(t_philo *philo, pthread_mutex_t *forks,
						t_prog *prog);
int					philo_dead(t_philo *philo, size_t dead_time);
int					dead_monitor(t_philo *philo);
#endif // PHILO_H
