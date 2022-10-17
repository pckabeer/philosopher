#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include <pthread.h>
#include <pthread.h>
#include <sys/time.h>




typedef struct philo
{
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int fork;
    pthread_t thread;
    struct timeval start_t;
    struct philo *next;
    
} t_philo;


#endif