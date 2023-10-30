/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:36 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:10:37 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*check_zeros(char *number)
{
	if (*number == '0' && *(number + 1))
	{
		while (*number == '0' && *(number + 1))
			number++;
		return (number);
	}
	return (number);
}

int	check(char *str)
{
	long long	atoi_check;
	size_t		len;
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = str;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		str++;
	str = check_zeros(str);
	len = ft_strlen(str);
	if (!len || len >= 12)
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	atoi_check = ft_atoi(tmp);
	if (atoi_check <= 0 || atoi_check > INT_MAX)
		return (-1);
	return (atoi_check);
}

int	parse_args(char **argv, t_philos *philos)
{
	size_t	i;

	i = 1;
	philos->limits->num_of_philos = check(argv[i++]);
	philos->limits->time_to_die = check(argv[i++]);
	philos->limits->time_to_eat = check(argv[i++]);
	philos->limits->time_to_sleep = check(argv[i++]);
	philos->limits->eat_lim = -1;
	if (argv[i])
	{
		philos->limits->eat_lim = check(argv[i++]);
		if (philos->limits->eat_lim < 0)
			return (quit(E_NEGNUM, philos));
	}
	if (philos->limits->num_of_philos < 0 || philos->limits->time_to_die < 0
		|| philos->limits->time_to_eat < 0 || philos->limits->time_to_sleep < 0)
		return (quit(E_NEGNUM, philos));
	return (EXIT_SUCCESS);
}
