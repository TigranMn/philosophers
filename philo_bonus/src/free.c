/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:18 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:10:19 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_single(void **addr)
{
	if (*addr)
	{
		free(*addr);
		*addr = 0;
	}
	return (0);
}

void	*free_all_mem(t_philos *philos)
{
	sem_close(philos->forks);
	sem_close(philos->print);
	sem_close(philos->finish);
	sem_close(philos->end);
	free_single((void *)&(philos->limits));
	free_single((void *)&(philos->philo_list));
	free_single((void *)&(philos));
	return (NULL);
}
