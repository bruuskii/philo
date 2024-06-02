/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 04:34:46 by izouine           #+#    #+#             */
/*   Updated: 2024/06/01 10:27:21 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t dead_time)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal_eaten >= dead_time && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo && i < philo[0].philo_nbr)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die) == 1)
		{
			print(&philo[i], "died");
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	eat_times(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (philo[0].nbr_of_meals != -1 && i < philo[0].philo_nbr)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo[i].meals_counter >= philo[0].nbr_of_meals)
			finished++;
		i++;
		pthread_mutex_unlock(philo->meal_lock);
	}
	if (finished == philo[0].philo_nbr)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death(philo) == 1 || eat_times(philo) == 1)
			break ;
	}
	return (arg);
}

void	print(t_philo *philo, char *s)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!dead_monitor(philo))
		printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(philo->write_lock);
}
