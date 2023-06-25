/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:57 by minabe            #+#    #+#             */
/*   Updated: 2023/06/25 17:48:12 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*init_data(int argc, char *argv[])
{
	int		i;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->num_philos = my_atoi(argv[1]);
	data->time_to_die = my_atoi(argv[2]);
	data->time_to_eat = my_atoi(argv[3]);
	data->time_to_sleep = my_atoi(argv[4]);
	if (data->num_philos < 2 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (NULL);
	if (argc == 6)
		data->num_of_times_each_philo_must_eat = atoi(argv[5]);
	else
		data->num_of_times_each_philo_must_eat = NOT_SET;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (data->forks == NULL)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	data->start_time = get_time();
	pthread_mutex_init(&data->log, NULL);
	return (data);
}

t_philo	*philo_data_init(t_data *data, int id)
{
	t_philo	*philo_data;

	philo_data = malloc(sizeof(t_philo));
	if (philo_data == NULL)
		return (NULL);
	philo_data->id = id;
	philo_data->eat_count = 0;
	philo_data->data = *data;
	philo_data->last_eat_time = 0;
	philo_data->is_dead = false;
	return (philo_data);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->log);
	free(data);
}
