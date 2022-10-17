/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:18:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/15 22:36:45 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, char **argv )
{
    int i;

    i = 0;
    while (i < atoi(argv[1]))
    {
        philo[i].fork = 0;
        philo[i].id = i;
        philo[i].time_to_sleep = atoi(argv[4]);
        philo[i].time_to_die = atoi(argv[2]);
        philo[i].time_to_eat = atoi(argv[3]);
        if (i == (atoi(argv[1])-1))
            philo[i].next = &philo[0];
        else
            philo[i].next = &philo[i+1];
        
        i++;
    }
    printf("Philo Generated : %d\n",i);

}

void print_philo(void *philoarg)
{
    //print philo 
}

void *routine(void *philoarg)
{
    struct timeval tv;
    t_philo *philo;
    
    philo = (t_philo *) philoarg;
    while(1)
    {
        eat(philo);
    }
    // philo->fork = 1;
    // philo->next->fork = 1;
    // eat()
    // sleep()
}

void *eat(t_philo *philo)
{
    struct timeval tv;
    // t_philo *philo;
    
    // philo = (t_philo *) philoarg;
    philo->fork=1;
    philo->next->fork=1;
    gettimeofday(&philo->start_t, NULL);
            printf(" Philosopher : %d \n",philo->id);

    while (tv.tv_usec <= (philo->start_t.tv_usec + (philo->time_to_eat * 1000)))
    {
        gettimeofday(&tv, NULL);
    }
    philo->fork = 0;
    philo->next->fork = 0;
    pthread_exit(NULL);    
}

// no of phil , time to die , tte,time to sleep , number of time each philosopher should eat

int main(int argc, char *argv[]) 
{
    t_philo *philo;
    int i;

    philo = malloc(sizeof(*philo) * atoi(argv[1]));
    i = -1;
    init_philo(philo, argv);
        while(++i<atoi(argv[1]))
            pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);

        // if(!(philo[0].fork)&&!(philo[0].next->fork))
        // if(!(philo[1].fork)&&!(philo[1].next->fork))
            // pthread_create(&philo[1].thread, NULL, eat, (void *) &philo[1]);
        // if(!(philo[2].fork)&&!(philo[2].next->fork))
            // pthread_create(&philo[2].thread, NULL, eat, (void *) &philo[2]);
        // if(!(philo[3].fork)&&!(philo[3].next->fork))
            // pthread_create(&philo[3].thread, NULL, eat, (void *) &philo[3]);
    while (1)
    { 
        // check death
    }
       
    



}
