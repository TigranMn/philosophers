/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:13:41 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:13:58 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long long	ft_atoi(char *number)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	if (*number == '-')
		sign = -1;
	if (*number == '-' || *number == '+')
		number++;
	number = check_zeros(number);
	while (*number)
	{
		result = ((result * 10) + (*number - '0'));
		number++;
	}
	return (result * sign);
}

void	ft_err(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}
