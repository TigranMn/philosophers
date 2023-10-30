/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:13:36 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:13:37 by tmnatsak         ###   ########.fr       */
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

void	ft_usleep(uint64_t sleep_time)
{
	uint64_t	start;

	start = ft_gettime();
	while (1)
	{
		if (ft_gettime() - start >= sleep_time)
			break ;
		usleep(50);
	}
}
