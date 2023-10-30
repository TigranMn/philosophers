/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:01:06 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:04:05 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	parse_args(argc, argv);
	init_data(argc, argv, &data);
	ft_gettime();
	while (i < data.num_of_philo)
	{
		pthread_create(&data.philos[i].philo, \
		NULL, &routine, (void *)&data.philos[i]);
		i++;
	}
	while (1)
	{
		if (all_philos_ate(&data) || some_philo_dead(&data))
			break ;
	}
	i = -1;
	while (++i < data.num_of_philo)
		pthread_join(data.philos[i].philo, NULL);
	rip_philos(&data);
	return (0);
}
