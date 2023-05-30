/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:46 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:32:12 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_s *s)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * s->nb_philos);
	if (!forks)
		return (free_s(s), NULL);
	i = 0;
	while (i < s->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (free_s(s), NULL);
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->s->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->s->nb_philos;
		philo->fork[1] = philo->id;
	}
}

t_philo	**init_philosophers(t_s *s)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * s->nb_philos);
	if (!philos)
		return (free_s(s), NULL);
	i = 0;
	while (i < s->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (free_s(s), NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (free_s(s), NULL);
		philos[i]->s = s;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

int	init_global_mutexes(t_s *s)
{
	s->fork_locks = init_forks(s);
	if (!s->fork_locks)
		return (0);
	if (pthread_mutex_init(&s->stop_mtx, 0) != 0)
		return (free_s(s), 0);
	if (pthread_mutex_init(&s->stdout_mtx, 0) != 0)
		return (free_s(s), 0);
	return (1);
}

t_s	*init_s(int ac, char **av, int i)
{
	t_s	*s;

	s = malloc(sizeof(t_s) * 1);
	if (!s)
		return (free_s(s), NULL);
	s->nb_philos = ft_atoi(av[i++]);
	s->time_to_die = ft_atoi(av[i++]);
	s->time_to_eat = ft_atoi(av[i++]);
	s->time_to_sleep = ft_atoi(av[i++]);
	s->must_eat = -1;
	if (ac - 1 == 5)
		s->must_eat = ft_atoi(av[i]);
	s->philos = init_philosophers(s);
	if (!s->philos)
		return (NULL);
	if (!init_global_mutexes(s))
		return (NULL);
	s->stop = 0;
	return (s);
}
