#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\r' || c == ' ' || c == '\n'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	nbr;
	int					sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
        if(str[i] >= '0' && str[i] <= '9')
		    nbr = (nbr * 10) + str[i++] - 48;
        else
            exit_error("Your input is not a digit!");
		if (nbr >= LLONG_MAX && sign == 1)
			return (-1);
		else if (nbr >= LLONG_MAX && sign == -1)
			return (0);
	}
	return ((int)(nbr * sign));
}

int exit_error(char *str)
{
    printf("%s\n", str);
    return 0;
}

size_t get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	size_t time = (tv.tv_sec / 1000) + (tv.tv_usec * 1000);
	return time;
}

void precise_usleep(size_t time)
{
	size_t start = get_time();
	while(get_time() - start < time)
		usleep(500);
}

void print(t_philo *philo, char *s)
{
	size_t time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if(!dead_monitor(philo))
		printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(philo->write_lock);
}