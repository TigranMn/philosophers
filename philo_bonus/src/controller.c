/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:03 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:10:06 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*wait_eat(void *arg)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = (t_philos *)arg;
	while (i < (int)philos->limits->num_of_philos)
	{
		waitpid(philos->philo_list[i].pid, NULL, 0);
		i++;
	}
	sem_post(philos->finish);
	return (NULL);
}

void	wait_any_action(t_philos *philos)
{
	pthread_t	*thread;
	int			i;

	thread = (pthread_t *)malloc(sizeof(pthread_t));
	sem_wait(philos->finish);
	if (pthread_create(thread, NULL, &wait_eat, (void *)philos))
		quit(E_THREAD, philos);
	sem_wait(philos->finish);
	if (pthread_detach(*thread))
		quit(E_THREAD, philos);
	free_single((void *)&thread);
	i = 0;
	while (i < (int)philos->limits->num_of_philos)
	{
		kill(philos->philo_list[i].pid, SIGTERM);
		i++;
	}
}

void	make_processes(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->limits->num_of_philos)
	{
		philos->philo_list[i].pid = fork();
		if (philos->philo_list[i].pid < 0)
			quit(E_PROCESS, philos);
		if (philos->philo_list[i].pid == 0)
		{
			if (i % 2)
				usleep(1000);
			start_routine(philos, &philos->philo_list[i]);
			exit(0);
		}
		i++;
	}
	wait_any_action(philos);
}

int	philos_routine(t_philos *philos)
{
	philos->philo_list = init_philo_list(philos, philos->limits->num_of_philos);
	if (!philos->philo_list)
		mem_issue(philos);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FINISH);
	sem_unlink(SEM_LAST_MEAL);
	philos->forks = sem_open(SEM_NAME, O_CREAT, 0755,
			philos->limits->num_of_philos);
	philos->print = sem_open(SEM_PRINT, O_CREAT, 0755, 1);
	philos->finish = sem_open(SEM_FINISH, O_CREAT, 0755, 1);
	philos->end = sem_open(SEM_LAST_MEAL, O_CREAT, 0755, 1);
	ft_gettime();
	make_processes(philos);
	free_all_mem(philos);
	return (EXIT_SUCCESS);
}
