/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:12 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:10:13 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*mem_issue(t_philos *philos)
{
	ft_err("Error during malloc\n");
	free_all_mem(philos);
	exit(E_NOMEM);
	return (NULL);
}

int	quit(int errno, t_philos *philos)
{
	if (errno == E_NEGNUM)
		ft_err("Invalid value of arguments\n");
	else if (errno == E_ARGSUM)
		ft_err("Invalid number of arguments\n");
	else if (errno == E_PROCESS)
		ft_err("Error creating child process\n");
	else if (errno == E_THREAD)
		ft_err("Error creating thread\n");
	if (philos)
		free_all_mem(philos);
	exit(EXIT_FAILURE);
}
