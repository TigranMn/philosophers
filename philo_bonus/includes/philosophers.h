/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmnatsak <tmnatsak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:07:53 by tmnatsak          #+#    #+#             */
/*   Updated: 2023/10/30 12:07:57 by tmnatsak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <limits.h>

# define SEM_NAME "/philo_semaphore"
# define SEM_PRINT "/philo_semaphore_msg"
# define SEM_FINISH "/philo_semaphore_finish"
# define SEM_LAST_MEAL "/philo_last_meal"

# define MSG_FORK_L  "has taken the left fork"
# define MSG_FORK_R  "has taken the right fork"
# define MSG_EAT   "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE   "died"

// Custom error codes
enum e_error {
	E_NOMEM,
	E_NEGNUM,
	E_ARGSUM,
	E_PROCESS,
	E_THREAD,
};

// Philo actions
enum e_flag {
	FLG_EAT,
	FLG_FORK,
	FLG_SLEEP,
	FLG_DIE,
	FLG_THINK	
};

// Philo Structures Defining
typedef struct philos_lim_s {
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_lim;
}	t_philos_lim;

typedef struct philo_s {
	int					id;
	int					eat_lim;
	pid_t				pid;
	unsigned int		last_meal;
	struct philos_s		*philos;
}	t_philo;

typedef struct philos_s {
	sem_t			*forks;
	sem_t			*print;
	sem_t			*finish;
	sem_t			*end;
	t_philos_lim	*limits;
	t_philo			*philo_list;
	int				die_flag;
}	t_philos;

int				philos_routine(t_philos *philos);
int				parse_args(char **argv, t_philos *philos);
char			*check_zeros(char *number);
int				check(char *str);
void			*start_routine(t_philos *philos, t_philo *philo);
t_philos		*init_philos(void);
t_philo			*init_philo_list(t_philos *philos, int num_of_philos);
size_t			ft_strlen(char *str);
long long		ft_atoi(char *number);
void			ft_err(char *s);
int				print_msg(t_philos *philos, t_philo *philo,
					char *msg, int flag);
void			print_death_msg(t_philos *philos,
					t_philo *philo, uint64_t time);
int				quit(int errno, t_philos *philos);
void			*mem_issue(t_philos *philos);
uint64_t		ft_gettime(void);
void			ft_usleep(uint64_t sleep_time);
void			*free_single(void **addr);
void			*free_all_mem(t_philos *philos);

#endif