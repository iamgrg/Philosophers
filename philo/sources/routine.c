/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:52 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:12:17 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->s->fork_locks[philo->fork[0]]);
	print_mutex("has taken a fork", philo);
	pthread_mutex_lock(&philo->s->fork_locks[philo->fork[1]]);
	print_mutex("has taken a fork", philo);
	print_mutex("is eating", philo);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_wait(philo->s, philo->s->time_to_eat);
	if (!simulation_ended(philo->s))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_mutex("is sleeping", philo);
	pthread_mutex_unlock(&philo->s->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->s->fork_locks[philo->fork[0]]);
	philo_wait(philo->s, philo->s->time_to_sleep);
}

void	think_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->s->time_to_die - (get_time_in_ms()
				- philo->last_meal) - philo->s->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (!time_to_think && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_mutex("is thinking", philo);
	philo_wait(philo->s, time_to_think);
}

void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->s->fork_locks[philo->fork[0]]);
	print_mutex("has taken a fork", philo);
	philo_wait(philo->s, philo->s->time_to_die);
	print_mutex("is died", philo);
	pthread_mutex_unlock(&philo->s->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->s->must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->s->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	begin_dinner(philo->s->start_time);
	if (philo->s->time_to_die == 0)
		return (NULL);
	if (philo->s->nb_philos == 1)
		return (single_philo(philo));
	else if (philo->id % 2)
		think_routine(philo, 1);
	while (!simulation_ended(philo->s))
	{
		eat_sleep_routine(philo);
		think_routine(philo, 0);
	}
	return (NULL);
}
