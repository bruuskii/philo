#include "philo_bonus.h"

void prog_init(t_philo *philos, t_prog *prog) {
    prog->death_flag = 0;
    prog->philo = philos;
    prog->dead_lock = sem_open("/dead_lock", O_CREAT, 0644, 1);
    prog->meal_lock = sem_open("/meal_lock", O_CREAT, 0644, 1);
    prog->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);

    if (prog->dead_lock == SEM_FAILED || prog->meal_lock == SEM_FAILED || prog->write_lock == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }
}


void	child_process(t_args *args,t_philo *philo,int id,  sem_t *forks, t_prog *prog)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		init_philo(args, id, forks, philo, prog);
		init_threads(philo, forks, prog);
	}
	else
	{
		printf("Parent process\n");
		exit(1);
	}

}



int	main(int argc, char **argv)
{
    int i;
    t_args args;
    t_prog prog;
    t_philo *philos;
    sem_t *forks;

    if (argc >= 5)
    {
        i = 0;
        init_args(&args, argc, argv);
        prog.forks = init_forks(args.philo_nbr);
        philos = malloc(sizeof(t_philo) * args.philo_nbr);
        if (philos == NULL) {
            exit_error("Memory allocation failed");
        }
        while (i < args.philo_nbr)
        {
            child_process(&args, &philos[i], i, prog.forks, &prog);
			printf("%d", i);
            i++;
        }
    }
}




