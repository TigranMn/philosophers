/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:01:11 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/28 16:04:24 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <time.h>
# include <stdint.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				*is_dead;
	int				meal_count;
	int				finished;
	uint64_t		last_eat;
	pthread_t		philo;
	struct s_data	*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*mutex_die;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_meal_count;
}			t_philo;

typedef struct s_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_eat;
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_die;
}	t_data;

int			ft_strlen(char *str);
void		ft_err(char *str);
void		parse_args(int argc, char **argv);
int			is_num(char *str);
int			ft_atoi(const char *str);
void		init_data(int argc, char **argv, t_data *data);
uint64_t	ft_gettime(void);
void		*routine(void *info);
void		ft_print(t_philo *philo, char *str, uint64_t time);
void		ft_usleep(t_philo *philo, uint64_t sleep_time);
int			is_dead(t_philo *philo);
int			all_philos_ate(t_data *data);
int			some_philo_dead(t_data *data);
void		rip_philos(t_data *data);

#endif