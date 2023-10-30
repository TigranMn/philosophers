/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:04:17 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:04:09 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (*(str + i) == ' ' || (*(str + i) > 8 && *(str + i) < 14))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			neg *= -1;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		res *= 10;
		res += *(str + i) - '0';
		i++;
	}
	return (res * neg);
}

void	ft_print(t_philo *philo, char *str, uint64_t time)
{
	pthread_mutex_lock(philo->mutex_print);
	if (!is_dead(philo))
		printf("[%llu ms] %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->mutex_print);
}

void	ft_usleep(t_philo *philo, uint64_t sleep_time)
{
	uint64_t	start;

	start = ft_gettime();
	while (!is_dead(philo))
	{
		if (ft_gettime() - start >= sleep_time)
			break ;
		usleep(50);
	}
}
