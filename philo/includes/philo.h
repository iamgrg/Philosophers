/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansard <gansard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:38 by gregoire          #+#    #+#             */
/*   Updated: 2023/04/29 15:32:12 by gansard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 250

typedef struct s_philo	t_philo;

typedef struct s_s
{
	int					must_eat;
	int					stop;
	unsigned int		nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	time_t				start_time;
	pthread_t			death;
	pthread_mutex_t		stop_mtx;
	pthread_mutex_t		stdout_mtx;
	pthread_mutex_t		*fork_locks;
	t_philo				**philos;
}						t_s;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_s					*s;
}						t_philo;

int						is_valid_format(int ac, char **av);
int						ft_atoi(char *str);
int						simulation_ended(t_s *s);
t_s						*init_s(int ac, char **av, int i);
void					*routine(void *data);
void					*death(void *data);
void					*free_s(t_s *s);
time_t					get_time_in_ms(void);
void					philo_wait(t_s *s, int wait_time);
void					begin_dinner(time_t start_time);
void					free_mutex(t_s *s);
void					print_mutex(char *str, t_philo *philo);

#endif