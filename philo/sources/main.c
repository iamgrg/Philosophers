/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:48 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:32:12 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->s->stdout_mtx);
	if (simulation_ended(philo->s) == 1)
	{
		pthread_mutex_unlock(&philo->s->stdout_mtx);
		return ;
	}
	printf("%ld %d %s\n",
		get_time_in_ms() - philo->s->start_time,
		philo->id,
		str);
	pthread_mutex_unlock(&philo->s->stdout_mtx);
}

int	start_simulation(t_s *s)
{
	unsigned int	i;

	s->start_time = get_time_in_ms() + (s->nb_philos * 2 * 10);
	i = 0;
	while (i < s->nb_philos)
	{
		if (pthread_create(&s->philos[i]->thread, NULL, &routine,
				s->philos[i]) != 0)
			return (free_s(s), 0);
		i++;
	}
	if (s->nb_philos > 1)
	{
		if (pthread_create(&s->death, NULL, &death, s) != 0)
			return (free_s(s), 0);
	}
	return (1);
}

void	stop_simulation(t_s *s)
{
	unsigned int	i;

	i = 0;
	while (i < s->nb_philos)
		pthread_join(s->philos[i++]->thread, NULL);
	if (s->nb_philos > 1)
		pthread_join(s->death, NULL);
	free_mutex(s);
	free_s(s);
}

int	main(int ac, char **av)
{
	t_s	*s;

	s = NULL;
	if (ac < 5 || ac > 6)
		return (printf("Invalid number of arguments\n"), 1);
	if (!is_valid_format(ac, av))
		return (printf("Invalid format\n"), 1);
	s = init_s(ac, av, 1);
	if (!s)
		return (printf("error : fail to init struct\n"), 1);
	if (!start_simulation(s))
		return (printf("error : fail to start simulation\n"), 1);
	stop_simulation(s);
	return (0);
}
