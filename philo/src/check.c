/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:50:30 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:03:54 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	some_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].mutex_last_eat);
		if (ft_gettime() - data->philos[i].last_eat >= data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_die);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->mutex_die);
			pthread_mutex_lock(&data->mutex_print);
			printf("[%llu ms] %d %s\n", ft_gettime(), (i + 1), "died");
			pthread_mutex_unlock(&data->mutex_print);
			pthread_mutex_unlock(&data->philos[i].mutex_last_eat);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].mutex_last_eat);
		i++;
	}
	return (0);
}

int	all_philos_ate(t_data *data)
{
	int	i;

	i = -1;
	while (data->num_of_eat != -1 && ++i < data->num_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].mutex_meal_count);
		if (data->philos[i].meal_count < data->num_of_eat)
		{
			pthread_mutex_unlock(&data->philos[i].mutex_meal_count);
			break ;
		}
		pthread_mutex_unlock(&data->philos[i].mutex_meal_count);
	}
	if (i == data->num_of_philo)
	{
		pthread_mutex_lock(&data->mutex_die);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->mutex_die);
		return (true);
	}
	return (false);
}

int	is_dead(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->mutex_die);
	flag = *(philo->is_dead);
	pthread_mutex_unlock(philo->mutex_die);
	return (flag);
}
