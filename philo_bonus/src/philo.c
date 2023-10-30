/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:13:27 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:13:29 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (argc < 5 || argc > 6)
		return (quit(E_ARGSUM, NULL));
	philos = init_philos();
	if (!philos)
		return (EXIT_FAILURE);
	if (parse_args(argv, philos))
		return (EXIT_FAILURE);
	if (philos_routine(philos))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
