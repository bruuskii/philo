#include "philo_bonus.h"

int	init_args(t_args *args, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		exit(1);
	args->philo_nbr = ft_atoi(argv[1]);
	args->philo_death_time = ft_atoi(argv[2]);
	args->philo_meal_time = ft_atoi(argv[3]);
	args->philo_sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		args->nbr_of_meals = ft_atoi(argv[5]);
	else
		args->nbr_of_meals = -1;
	if (args->philo_nbr > 200 || args->philo_nbr < 1)
		exit_error("Check again the number of philosophers");
	if (args->philo_death_time < 60 || args->philo_meal_time < 60
		|| args->philo_sleep_time < 60)
		exit_error("Check again the other inputs!");
	return (1);
}

sem_t* init_forks(int philo_nbr) {
    sem_t *forks = sem_open("/forks", O_CREAT, 0644, philo_nbr);
    if (forks == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }
    return forks;
}

int	init_philo(t_args *args, int id, sem_t *forks,
		t_philo *philo, t_prog *prog)
{
	philo->id = id;
	philo->philo_nbr = args->philo_nbr;
	philo->time_to_die = args->philo_death_time;
	philo->time_to_eat = args->philo_meal_time;
	philo->time_to_sleep = args->philo_sleep_time;
	philo->meals_eaten = 0;
	philo->start_time = get_time();
	philo->id = id + 1;
	philo->last_meal_eaten = get_time();
	philo->dead_lock = prog->dead_lock;
	philo->meal_lock = prog->meal_lock;
	philo->write_lock = prog->write_lock;
	philo->eating = 0;
	philo->nbr_of_meals = args->nbr_of_meals;
	philo->dead = &prog->death_flag;
	return (1);
}

int	init_threads(t_philo *philo, sem_t *forks, t_prog *prog)
{
	pthread_t	thread;
	int			i;

	i = 0;
	printf("init_threads\n");
	if (pthread_create(&thread, NULL, &monitor, prog->philo) != 0)
		exit_error("Error creating monitor thread");
	pthread_create(&philo->thread, NULL, &routine, philo);
	if (pthread_join(thread, NULL) != 0)
		exit_error("Error joining monitor thread");
	if (pthread_join(philo->thread, NULL) != 0)
		exit_error("Error joining routine thread");
	return (0);
}
