/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:01:14 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:04:01 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_err(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

static void	is_valid_arg(int argc, char **argv)
{
	int	i;
	int	philos;

	i = 2;
	philos = ft_atoi(argv[1]);
	if (philos <= 0 || philos > 200)
		ft_err("Error: Wrong number of philosophers\n");
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			ft_err("Error: Wrong arguments\n");
		i++;
	}
}

void	parse_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		ft_err("Error: Wrong number of arguments\n");
	while (i < argc)
	{
		if (!is_num(argv[i]))
			ft_err("Error: Wrong arguments\n");
		i++;
	}
	is_valid_arg(argc, argv);
}
