/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:03:29 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:03:58 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].last_eat = 0;
		data->philos[i].data = data;
		data->philos[i].mutex_die = &data->mutex_die;
		data->philos[i].mutex_print = &data->mutex_print;
		data->philos[i].is_dead = &data->is_dead;
		data->philos[i].finished = 0;
		if (pthread_mutex_init(&data->philos[i].mutex_meal_count, NULL))
			ft_err("Error initializing mutex");
		if (pthread_mutex_init(&data->philos[i].mutex_last_eat, NULL))
			ft_err("Error initializing mutex");
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num_of_philo);
	if (!data->forks)
		ft_err("Error: Malloc\n");
	while (++i < data->num_of_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_err("Error initializing mutex");
	i = 0;
	while (i < data->num_of_philo)
	{
		if (i == data->num_of_philo - 1)
		{
			data->philos[i].r_fork = &data->forks[0];
			data->philos[i].l_fork = &data->forks[i];
		}
		else
		{
			data->philos[i].l_fork = &data->forks[i];
			data->philos[i].r_fork = &data->forks[i + 1];
		}
		i++;
	}
}

void	init_data(int argc, char **argv, t_data *data)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_of_eat = -1;
	if (argc == 6)
		data->num_of_eat = ft_atoi(argv[5]);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philos)
		ft_err("Error: malloc\n");
	data->is_dead = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_die, NULL);
	init_forks(data);
	init_philos(data);
}
