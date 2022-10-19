#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>


/*
    is_sleep - when the philosopher is sleeping
    fork 
    thinking - when is_sleep and fork is 0;

*/

typedef struct info
{
	int p_dead;
	int no_phil;
	pthread_mutex_t dlock;
	pthread_mutex_t print_lock;
	int p_lock;

}t_info;
typedef struct philo
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int rounds;
    int fork;
    int m_fork;
	long life;
	int is_dead;
    int is_sleep;
    pthread_t thread;
	pthread_mutex_t lock;
    struct timeval start_t;
    struct timeval life_t;
    struct philo *next;
    struct info *key;
    
} t_philo;

 int is_dead(t_philo  *philo);
 void ft_muteall(t_philo  *philo,int flag);
void print_info(t_philo  *philo,int print_order);

#endif