/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:13:32 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:13:33 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *args)
{
	unsigned int	time;
	t_philos		*philos;
	t_philo			*philo;

	philo = (t_philo *)args;
	philos = philo->philos;
	while (1)
	{
		sem_wait(philos->end);
		time = ft_gettime();
		if (philos->die_flag)
		{
			sem_post(philos->end);
			return (NULL);
		}
		if ((time - philo->last_meal)
			> (unsigned int)philos->limits->time_to_die)
		{
			print_death_msg(philos, philo, time);
			sem_post(philos->end);
			return (NULL);
		}
		sem_post(philos->end);
	}
	return (NULL);
}

void	philo_sleep(t_philos *philos, t_philo *philo)
{
	print_msg(philos, philo, MSG_SLEEP, FLG_SLEEP);
	ft_usleep(philos->limits->time_to_sleep);
	print_msg(philos, philo, MSG_THINK, FLG_THINK);
}

int	philo_eat(t_philos *philos, t_philo *philo)
{
	sem_wait(philos->forks);
	print_msg(philos, philo, MSG_FORK_L, FLG_FORK);
	sem_wait(philos->forks);
	print_msg(philos, philo, MSG_FORK_R, FLG_FORK);
	if (print_msg(philos, philo, MSG_EAT, FLG_EAT))
	{
		sem_wait(philos->end);
		philos->die_flag = 1;
		sem_post(philos->end);
		sem_post(philos->forks);
		sem_post(philos->forks);
		return (EXIT_FAILURE);
	}
	ft_usleep(philos->limits->time_to_eat);
	sem_post(philos->forks);
	sem_post(philos->forks);
	philo_sleep(philos, philo);
	return (EXIT_SUCCESS);
}

void	one_philo_action(t_philos *philos, t_philo *philo)
{
	print_msg(philos, philo, MSG_FORK_L, FLG_FORK);
	ft_usleep(philos->limits->time_to_die);
	sem_wait(philos->end);
	philos->die_flag = 1;
	sem_post(philos->end);
	print_death_msg(philos, philo, ft_gettime());
}

void	*start_routine(t_philos *philos, t_philo *philo)
{
	pthread_t	tid;

	if (philos->limits->num_of_philos == 1)
	{
		one_philo_action(philos, philo);
		return (NULL);
	}
	if (pthread_create(&tid, NULL, &check_death, (void *)philo))
		return (NULL);
	while (1)
	{
		if (philo_eat(philos, philo))
			break ;
		sem_wait(philos->end);
		if (philos->die_flag)
		{
			sem_post(philos->end);
			break ;
		}
		sem_post(philos->end);
	}
	if (pthread_join(tid, NULL))
		return (NULL);
	return (NULL);
}
