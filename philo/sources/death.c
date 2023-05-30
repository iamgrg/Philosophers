/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:42 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:09:14 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop(t_s *s, int state)
{
	pthread_mutex_lock(&s->stop_mtx);
	s->stop = state;
	pthread_mutex_unlock(&s->stop_mtx);
}

int	simulation_ended(t_s *s)
{
	int	r;

	r = 0;
	pthread_mutex_lock(&s->stop_mtx);
	if (s->stop == 1)
		r = 1;
	pthread_mutex_unlock(&s->stop_mtx);
	return (r);
}

int	philo_starvation(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->s->time_to_die)
	{
		set_stop(philo->s, 1);
		printf("%ld %d is died\n",
			get_time_in_ms() - philo->s->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (1);
	}
	return (0);
}

int	end_condition_reached(t_s *s)
{
	unsigned int	i;
	int				all_ate_enough;

	all_ate_enough = 1;
	i = 0;
	while (i < s->nb_philos)
	{
		pthread_mutex_lock(&s->philos[i]->meal_time_lock);
		if (philo_starvation(s->philos[i]))
			return (1);
		if (s->must_eat != -1)
			if (s->philos[i]->times_ate < (unsigned int)s->must_eat)
				all_ate_enough = 0;
		pthread_mutex_unlock(&s->philos[i]->meal_time_lock);
		i++;
	}
	if (s->must_eat != -1 && all_ate_enough == 1)
	{
		set_stop(s, 1);
		return (1);
	}
	return (0);
}

void	*death(void *data)
{
	t_s	*s;

	s = (t_s *)data;
	if (!s->must_eat)
		return (NULL);
	set_stop(s, 0);
	begin_dinner(s->start_time);
	while (1)
	{
		if (end_condition_reached(s) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
