/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 04:35:13 by izouine           #+#    #+#             */
/*   Updated: 2024/05/27 04:35:15 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->first_fork);
	print(philo, "has taken a fork");
	if (philo->philo_nbr == 1)
	{
		precise_usleep(philo->time_to_die);
		sem_post(philo->first_fork);
		return ;
	}
	sem_wait(philo->second_fork);
	print(philo, "has taken a fork");
	philo->eating = 1;
	print(philo, "is eating");
	sem_wait(philo->meal_lock);
	philo->last_meal_eaten = get_time();
	philo->meals_counter++;
	sem_post(philo->meal_lock);
	precise_usleep(philo->time_to_eat);
	philo->eating = 0;
	sem_post(philo->first_fork);
	sem_post(philo->second_fork);
}

void	sleeping(t_philo *philo)
{
	print(philo, "sleeping");
	precise_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print(philo, "thinking");
}

int	dead_monitor(t_philo *philo)
{
	sem_wait(philo->dead_lock);
	if (*philo->dead == 1)
		return (sem_post(philo->dead_lock), 1);
	sem_post(philo->dead_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		precise_usleep(1);
	}
	while (!dead_monitor(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
