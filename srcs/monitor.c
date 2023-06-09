/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:25:36 by minabe            #+#    #+#             */
/*   Updated: 2023/07/10 12:38:06 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_dead(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->shered->mutex);
	time = (get_time() - philo->last_eat_time) / 1000;
	if (philo->is_eating == false && philo->shered->death_time < time)
	{
		pthread_mutex_unlock(&philo->shered->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->shered->mutex);
	return (false);
}

void	*monitor(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->shered->mutex);
	while (philo->shered->is_dead == false)
	{
		pthread_mutex_unlock(&philo->shered->mutex);
		if (check_dead(philo))
		{
			print_log(philo, "died");
			pthread_mutex_lock(&philo->shered->mutex);
			philo->shered->is_dead = true;
			pthread_mutex_unlock(&philo->shered->mutex);
		}
		pthread_mutex_lock(&philo->shered->mutex);
		if (philo->shered->finished == philo->shered->num_of_philos)
			philo->shered->is_dead = true;
		pthread_mutex_unlock(&philo->shered->mutex);
		pthread_mutex_lock(&philo->shered->mutex);
	}
	pthread_mutex_unlock(&philo->shered->mutex);
	pthread_mutex_lock(&philo->shered->mutex);
	philo->shered->monitor_end++;
	pthread_mutex_unlock(&philo->shered->mutex);
	return (NULL);
}
