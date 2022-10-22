/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:01:27 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/22 15:59:25 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
#include <semaphore.h>

/*
    is_sleep - when the philosopher is sleeping
    fork 
    thinking - when is_sleep and fork is 0;

*/

typedef struct info
{
	int				p_dead;
	int				no_phil;
	pthread_mutex_t	dlock;
	pthread_mutex_t	print_lock;
	int				p_lock;
}t_info;
typedef struct philo
{
	int				id;
	int				pid;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				rounds;
	int				fork;
	int				m_fork;
	long			life;
	sem_t			*my_fork;
	sem_t			*my_death;
	sem_t			*print;
	pthread_t		thread;
	pthread_mutex_t	lock;
	pthread_mutex_t	rlock;
	struct timeval	start_t;
	struct timeval	life_t;
	struct philo	*next;
	struct info		*key;
}	t_philo;

int		is_dead(t_philo *philo);
void	ft_muteall(t_philo *philo, int flag);
void	print_info(t_philo *philo, int print_order);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
long	n_timestamp(struct timeval *time);
size_t	timestamp_new(void);
int		ft_atoi(const char *str);
int		t_sleep(t_philo *philo, int ttime);
int		ft_sleep(t_philo *philo);
void	print_info(t_philo *philo, int print_order);
int		is_dead(t_philo *philo);
void	ft_muteall(t_philo *philo, int flag);
int		fork_mask(t_philo *philo);
void	lock_order(t_philo *philo);
int		*single_t_sleep(t_philo *philo, int ttime);

#endif