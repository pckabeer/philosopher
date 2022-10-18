/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:18:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/18 11:44:58 by kpanikka         ###   ########.fr       */
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
        philo[i].time_to_die = atoi(argv[2]);
        philo[i].life = atoi(argv[2]);
        philo[i].time_to_sleep = atoi(argv[4]);
        philo[i].time_to_eat = atoi(argv[3]);
		gettimeofday(&philo->life_t, NULL);
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

void ft_sleep(t_philo *philo)
{
    struct timeval tv;
    
    gettimeofday(&philo->start_t, NULL);
    // while (tv.tv_sec <= (philo->start_t.tv_sec + (philo->time_to_sleep * 1000)))
    // {
	// 	printf("hi --- \n");
	//     gettimeofday(&tv, NULL);
	// }
	usleep(philo->time_to_sleep*1000);
}


/*
    Function finishes eat and ft_sleep then comes out
*/
void eat(t_philo *philo)
{
    struct timeval tv;
    
	philo->fork=1;
    philo->next->fork=1;
    pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
    gettimeofday(&philo->start_t, NULL);
    printf("%ld %d has taken a fork \n",philo->start_t.tv_sec,philo->id);
    printf("%ld %d is eating \n",philo->start_t.tv_sec,philo->id);

	usleep(philo->time_to_eat*1000);

    // while (tv.tv_usec <= (philo->start_t.tv_usec + (philo->time_to_eat * 1000)))
    // {
    //     gettimeofday(&tv, NULL);
    // }
    //time to die will be full
    //check is_sleep fork
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->next->lock);
    philo->fork = 0;
    philo->next->fork = 0;
	//philo->life = philo->time_to_die;
	gettimeofday(&philo->life_t, NULL);

    printf("%ld %d is sleeping \n",philo->start_t.tv_sec,philo->id);
    ft_sleep(philo);
    //philo->time_to_die = philo->time_to_die - philo->time_to_sleep; // reduces the sleeping time
	//philo->life =// philo->time_to_die - philo->time_to_sleep;
    printf("%ld %d is thinking \n",philo->start_t.tv_sec,philo->id);
}

void *routine(void *philoarg)
{
    struct timeval tv;
    t_philo *philo;
    
    philo = (t_philo *) philoarg;
    while(1)
    {
		if(philo->id%2)
		{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
		}
		else
		{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
		}
        if(!(philo->fork) && !(philo->next->fork))
            eat(philo);
			
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
    }
    pthread_exit(NULL);

}

// no of phil , time to die , tte,time to sleep , number of time each philosopher should eat

int main(int argc, char *argv[]) 
{
    t_philo	*philo;
    int		i;

	printf("hi \n");
    philo = malloc(sizeof(t_philo) * atoi(argv[1]));
    i = -1;
    init_philo(philo, argv);
        while(++i<atoi(argv[1]))
            pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
    i = -1;

    while (1)
    { 
        // check death0
		while (++i<atoi(argv[1]))
		{
			// check for death of each 
			// print the death message
			// free variables
			// free mutex
			// if died exi the program
		}
		
    }
       
    



}
