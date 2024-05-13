#include "philo.h"

void prog_init(t_philo *philos, t_prog *prog)
{
    prog->death_flag = 0;
    prog->philo = philos;
    pthread_mutex_init(&prog->dead_lock, NULL);
    pthread_mutex_init(&prog->meal_lock, NULL);
    pthread_mutex_init(&prog->write_lock, NULL);
}

int main(int argc, char **argv)
{
    t_philo philo[ALL_PHILOS];
    t_args args;
    t_prog prog;
    pthread_mutex_t forks[ALL_PHILOS];
    if(argc == 5 || argc == 6)
    {
        if(!init_args(&args, argc, argv))
            exit_error("what the fuck");
        init_forks(forks, &args);

        if(!init_philo(&args, &prog, forks, philo))
            exit_error("what the hell");
        if(!init_threads(philo, forks, &prog))
            exit_error("what the shiii");
        printf("man\n");
    }
    //destroy_all_threads();
    else
        exit_error("what are you doing");
}