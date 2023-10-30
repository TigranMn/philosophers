/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:43:22 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:03:48 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	ft_gettime(void)
{
	struct timeval	timeval;
	static uint64_t	start;
	static int		count;

	gettimeofday(&timeval, NULL);
	if (count == 0)
	{
		start = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
		count++;
	}
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000) - start);
}

void	pick_forks(t_philo *philo)
{
	if (philo->id == philo->data->num_of_philo)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "has taken the right fork", ft_gettime());
		if (philo->data->num_of_philo == 1)
		{
			ft_usleep(philo, philo->data->time_to_sleep);
			exit(1);
		}
		pthread_mutex_lock(philo->l_fork);
		ft_print(philo, "has taken the left fork", ft_gettime());
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_print(philo, "has taken the left fork", ft_gettime());
		pthread_mutex_lock(philo->r_fork);
		ft_print(philo, "has taken the right fork", ft_gettime());
	}
}

void	philo_cycle(t_philo *philo)
{
	while (!is_dead(philo))
	{
		pick_forks(philo);
		ft_print(philo, "is eating", ft_gettime());
		pthread_mutex_lock(&philo->mutex_last_eat);
		philo->last_eat = ft_gettime();
		pthread_mutex_unlock(&philo->mutex_last_eat);
		ft_usleep(philo, philo->data->time_to_eat);
		pthread_mutex_lock(&philo->mutex_meal_count);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->mutex_meal_count);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		ft_print(philo, "is sleeping", ft_gettime());
		ft_usleep(philo, philo->data->time_to_sleep);
		ft_print(philo, "is thinking", ft_gettime());
	}
}

void	*routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = ft_gettime();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo_cycle(philo);
	philo->finished = 1;
	return (0);
}

void	rip_philos(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_die);
	pthread_mutex_destroy(&data->mutex_print);
	while (i < data->num_of_philo)
	{
		if (data->num_of_philo != 1 || data->philos[i].finished)
		{
			pthread_mutex_destroy(&data->philos[i].mutex_last_eat);
			pthread_mutex_destroy(&data->philos[i].mutex_meal_count);
			pthread_mutex_destroy(&data->forks[i]);
		}
		i++;
	}
	free(data->forks);
	if (data->num_of_philo != 1)
		free(data->philos);
}
