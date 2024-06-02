#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int				id;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				philo_nbr;
	size_t			start_time;
	size_t			last_meal_eaten;
	sem_t       	*first_fork;
	sem_t       	*second_fork;
	int				meals_counter;
	pthread_t		thread;
	sem_t	        *dead_lock;
	sem_t	        *meal_lock;
	sem_t	        *write_lock;
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
	sem_t       	*dead_lock;
	sem_t       	*meal_lock;
	sem_t       	*write_lock;
	t_philo			*philo;
	sem_t 	 		*forks;
}					t_prog;

int	init_args(t_args *args, int argc, char **argv);
sem_t* init_forks(int philo_nbr);
int	init_philo(t_args *args, int id, sem_t *forks,
		t_philo *philo, t_prog *prog);
int	init_threads(t_philo *philo, sem_t *forks, t_prog *prog);
int	philo_dead(t_philo *philo, size_t dead_time);
int	check_death(t_philo *philo);
int	eat_times(t_philo *philo);
void	*monitor(void *arg);
void	print(t_philo *philo, char *s);
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
int	dead_monitor(t_philo *philo);
void	*routine(void *arg);
int	ft_atoi(const char *s);
int	exit_error(char *str);
size_t	get_time(void);
void	precise_usleep(size_t time);


#endif // PHILO_BONUS_H