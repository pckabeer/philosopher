/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:18:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/19 10:16:11 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
timestamp for current time witgh the diffrence of philo started
*/
long n_timestamp(struct timeval *time)
{
	struct timeval n_time;
	
	gettimeofday(&n_time, NULL);
	return (((n_time.tv_sec - time->tv_sec)*1000) + 
		((n_time.tv_usec - time->tv_usec)/1000));
}

size_t timestamp_new()
{
	struct timeval n_time;
	
	gettimeofday(&n_time, NULL);
	return ((n_time.tv_sec * 1000000)+ (n_time.tv_usec));
}

void init_philo(t_philo *philo, char **argv )
{
    int i;

    i = 0;
    while (i < atoi(argv[1]))
    {
		philo[i].fork = 0;
        philo[i].m_fork = 0;
        philo[i].id = i + 1;
        philo[i].time_to_die = atoi(argv[2]);
        //philo[i].life = atoi(argv[2]);
        philo[i].time_to_sleep = atoi(argv[4]);
		if(atoi(argv[5]))
			philo[i].round = atoi(argv[5]);
		else
			philo[i].round = -1;
        philo[i].time_to_eat = atoi(argv[3]);
		gettimeofday(&philo[i].life_t, NULL);
		philo[i].life = n_timestamp(&philo[i].life_t);
		if (i == (atoi(argv[1])-1))
            philo[i].next = &philo[0];
        else
            philo[i].next = &philo[i+1];
        i++;
    }
}

void ft_sleep(t_philo *philo)
{
	size_t ts;
	size_t target;
	
	ts =timestamp_new();
	target = ts +(philo->time_to_sleep*1000);
	 while (ts < target)
	 {
		ts =timestamp_new();
		//usleep(350);
	 }
}

/*
    Function finishes eat and ft_sleep then comes out
*/
void eat(t_philo *philo)
{
	philo->fork=1;
    philo->next->fork=1;
	philo->m_fork = philo->id;
	philo->next->m_fork = philo->id;
    pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
    printf("%ld %d has taken a fork \n",n_timestamp(&philo->life_t),philo->id);
    printf("%ld %d is eating \n",n_timestamp(&philo->life_t),philo->id);


	size_t ts,target;
	ts = timestamp_new();
	target = ts +(philo->time_to_eat*1000);
	 while (ts < target)
	 {
		ts = timestamp_new();
		//usleep(350);
	 }
	 
    //check is_sleep fork
	if(!philo->id%2)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
	}
	else
	{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
	}
    philo->fork = 0;
    philo->next->fork = 0;
	//philo->life = philo->time_to_die;
	philo->life = n_timestamp(&philo->life_t);

    printf("%ld %d is sleeping \n",n_timestamp(&philo->life_t),philo->id);
    ft_sleep(philo);
    //philo->time_to_die = philo->time_to_die - philo->time_to_sleep; // reduces the sleeping time
	//philo->life =// philo->time_to_die - philo->time_to_sleep;
    printf("%ld %d is thinking \n",n_timestamp(&philo->life_t),philo->id);
}

void *routine(void *philoarg)
{
    struct timeval tv;
    t_philo *philo;
    
    philo = (t_philo *) philoarg;
    while(1)
    {
		if(!philo->id%2)
		{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
		}
		else
		{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
		}
		
        if(!(philo->fork) && !(philo->next->fork) && philo->rounds)
            eat(philo);
			
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
		//usleep(350);
    }
    pthread_exit(NULL);

}

void kill_all(t_philo *philos,int no_phil)
{
	int i;

	i = -1;
	while (++i < no_phil)
		{
			if (!philos[i].is_dead)
			{
				philos[i].is_dead = 1;
				//printf("%ld %d died \n",n_timestamp(&philos[i].life_t),philos[i].id);
			}
			
		}
		// free variables
				// free mutex
				// exit program
				exit(1);
	
}

int is_dead(t_philo  *philo)
{
	long n_time;

	n_time = n_timestamp(&philo->life_t);
	if (n_time - philo->life > (philo->time_to_die))
	{
		printf("%ld %d died \n",n_timestamp(&philo->life_t),philo->id);
		philo->is_dead = 1;
		return 1;
	}
	return 0;
}
// no of phil , time to die , tte,time to sleep , number of time each philosopher should eat

int main(int argc, char *argv[]) 
{
    t_philo	*philo;
    int		i;

    philo = malloc(sizeof(t_philo) * atoi(argv[1]));
    i = -1;
    init_philo(philo, argv);
	while(++i<atoi(argv[1]))
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
    while (1)
    { 
		i = -1;
		//usleep(500);
		while (++i < atoi(argv[1]))
		{
			if (is_dead(&philo[i]))
				kill_all(philo,atoi(argv[1]));
		}
    }
}
