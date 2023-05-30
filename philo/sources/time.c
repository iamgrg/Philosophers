/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:54 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:23:22 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_wait(t_s *s, int wait_time)
{
	time_t	end;

	end = get_time_in_ms() + wait_time;
	while (get_time_in_ms() < end)
	{
		if (simulation_ended(s))
			break ;
		usleep(100);
	}
}

void	begin_dinner(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		;
}
