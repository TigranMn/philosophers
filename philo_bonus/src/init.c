/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:31 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:10:32 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philos	*init_philos(void)
{
	t_philos	*philos;

	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		return (mem_issue(philos));
	philos->forks = NULL;
	philos->print = NULL;
	philos->finish = NULL;
	philos->philo_list = NULL;
	philos->limits = (t_philos_lim *)malloc(sizeof(t_philos_lim));
	if (!philos->limits)
		return (mem_issue(philos));
	philos->die_flag = 0;
	return (philos);
}

t_philo	*init_philo_list(t_philos *philos, int num_of_philos)
{
	t_philo	*philo_list;
	int		i;

	i = 0;
	philo_list = (t_philo *)malloc(sizeof(t_philo) * num_of_philos);
	if (!philo_list)
		return (NULL);
	while (i < num_of_philos)
	{
		philo_list[i].id = i;
		philo_list[i].pid = 0;
		philo_list[i].last_meal = 0;
		philo_list[i].eat_lim = 0;
		philo_list[i].philos = philos;
		i++;
	}
	return (philo_list);
}
