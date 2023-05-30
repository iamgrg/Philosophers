/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:44 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:32:12 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_s(t_s *s)
{
	unsigned int	i;

	if (!s)
		return (NULL);
	if (s->fork_locks)
		free(s->fork_locks);
	if (s->philos)
	{
		i = 0;
		while (i < s->nb_philos)
		{
			if (s->philos[i])
				free(s->philos[i]);
			i++;
		}
		free(s->philos);
	}
	free(s);
	return (NULL);
}

void	free_mutex(t_s *s)
{
	unsigned int	i;

	i = 0;
	while (i < s->nb_philos)
	{
		pthread_mutex_destroy(&s->fork_locks[i]);
		pthread_mutex_destroy(&s->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&s->stdout_mtx);
	pthread_mutex_destroy(&s->stop_mtx);
}
