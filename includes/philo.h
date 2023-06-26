/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:22:47 by minabe            #+#    #+#             */
/*   Updated: 2023/06/26 14:44:21 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define NOT_SET -1

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			eat_count;
	long long	last_eat_time;
	bool		is_dead;
	t_data		data;
}	t_philo;

void		*philosopher(void *d);
void		*monitor(void *d);

t_data		*init_data(int argc, char *argv[]);
t_philo		*philo_data_init(t_data *data, int id);
void		destroy_data(t_data *data);

void		eating(t_philo *philo_data);
void		sleeping(t_philo *philo_data);
void		take_forks(t_philo *philo_data);
void		put_forks(t_philo *philo_data);
void		thinking(t_philo *philo_data);

int			first(t_philo *philo_data);
int			second(t_philo *philo_data);
long long	get_time(void);
long long	get_time_diff(long long time);
void		print_time_diff(long long time);
int			my_atoi(const char *str);
void		my_usleep(long long action_time);

#endif