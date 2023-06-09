/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:22:47 by minabe            #+#    #+#             */
/*   Updated: 2023/07/10 12:15:30 by minabe           ###   ########.fr       */
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

typedef struct s_shered
{
	int				num_of_philos;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				num_of_eat;
	long long		start_time;
	bool			is_dead;
	int				monitor_end;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
}	t_shered;

typedef struct s_philo
{
	t_shered	*shered;
	int			id;
	int			eat_count;
	long long	last_eat_time;
	bool		is_eating;
}	t_philo;

void		*monitor(void *arg);
int			thread(t_philo **philo_data, t_shered *shered);

t_shered	*init_shered_data(int argc, char *argv[]);
t_philo		**init_philo_data(t_shered *shered);
void		destroy_shered_data(t_shered *shered);

void		philo_exit(t_philo **philo_data, t_shered *shered);
int			philo_error(t_philo **philo_data, t_shered *shered);
void		philo_success(t_philo **philo_data, t_shered *shered);

int			eating(t_philo *philo_data);
void		sleeping(t_philo *philo_data);
void		thinking(t_philo *philo_data);

int			first(t_philo *philo_data);
int			second(t_philo *philo_data);
long long	get_time(void);
long long	get_time_diff(long long time);
void		print_time_diff(long long time);
int			my_atoi(const char *str);
void		my_usleep(long long action_time);
int			print_log(t_philo *philo_data, char *str);

#endif