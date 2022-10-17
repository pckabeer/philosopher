#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include <pthread.h>
#include <pthread.h>
#include <sys/time.h>


/*
    is_sleep - when the philosopher is sleeping
    fork 
    thinking - when is_sleep and fork is 0;

*/

typedef struct philo
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int fork;
    int is_sleep;
    pthread_t thread;
    struct timeval start_t;
    struct philo *next;
} t_philo;
#endif