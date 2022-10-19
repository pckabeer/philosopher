/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:18:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/19 22:50:00 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	unsigned int	num;

	num = n;
	if (n < 0)
	{
		write(1, "-", 1);
		num = -n;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
		ft_putchar(num % 10 + '0');
	//write(1, &(char)(num % 10 + '0'), 1);
}


void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

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

void init_philo(t_philo *philo, int argc, char **argv )
{
    int i;

    i = 0;
	t_info *t;

	t = malloc(sizeof(t_info));
	t->p_dead = 0;
	pthread_mutex_init(&t->print_lock,NULL);
	pthread_mutex_init(&t->dlock,NULL);

    while (i < atoi(argv[1]))
    {
		philo[i].fork = 0;
        philo[i].m_fork = 0;
        philo[i].id = i + 1;
        philo[i].key = t;
		pthread_mutex_init(&philo[i].lock,NULL);
        philo[i].key->no_phil = atoi(argv[1]);
		
        philo[i].time_to_die = atoi(argv[2]);
        //philo[i].life = atoi(argv[2]);
        philo[i].time_to_sleep = atoi(argv[4]);
		if(argc == 6)
			philo[i].rounds = atoi(argv[5]);
		else
			philo[i].rounds = -1;
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

int ft_sleep(t_philo *philo)
{
	size_t ts;
	size_t target;
	
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
	ts =timestamp_new();
	target = ts +(philo->time_to_sleep*1000);
	 while (ts < target)
	 {
		if (is_dead(philo))// || philo->key->p_dead)
				return(1);
		ts =timestamp_new();
		//usleep(350);
	 }
	if(philo->id%philo->key->no_phil)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
	}
	else
	{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
	}
	 return(0);
}

/*
    Function finishes eat and ft_sleep then comes out
*/
int eat(t_philo *philo)
{
	philo->fork=1;
    philo->next->fork=1;
	philo->m_fork = philo->id;
	philo->next->m_fork = philo->id;
	philo->life = n_timestamp(&philo->life_t);
    pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
    // printf("%ld %d has taken a fork \n",n_timestamp(&philo->life_t),philo->id);
	pthread_mutex_lock(&philo->key->print_lock);
	print_info(philo,1);
	pthread_mutex_unlock(&philo->key->print_lock);
	pthread_mutex_lock(&philo->key->print_lock);
	print_info(philo,1);
	pthread_mutex_unlock(&philo->key->print_lock);
	pthread_mutex_lock(&philo->key->print_lock);
	print_info(philo,2);
	pthread_mutex_unlock(&philo->key->print_lock);

    // printf("%ld %d has taken a fork \n",n_timestamp(&philo->life_t),philo->id);
    // printf("%ld %d is eating \n",n_timestamp(&philo->life_t),philo->id);


	size_t ts,target;
	ts = timestamp_new();
	target = ts +(philo->time_to_eat*1000);
	 while (ts < target)
	 {
		if (is_dead(philo))// || philo->key->p_dead)
			return 1 ;
		ts = timestamp_new();
		//usleep(350);
	 }
	 
    //check is_sleep fork
	if(philo->id%philo->key->no_phil)
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
	philo->rounds--;

	pthread_mutex_lock(&philo->key->print_lock);
	print_info(philo,3);
	pthread_mutex_unlock(&philo->key->print_lock);
    // printf("%ld %d is sleeping \n",n_timestamp(&philo->life_t),philo->id);
	if(ft_sleep(philo))
		return(1);
	pthread_mutex_lock(&philo->key->print_lock);
	print_info(philo,4);
	pthread_mutex_unlock(&philo->key->print_lock);
    // printf("%ld %d is thinking \n",n_timestamp(&philo->life_t),philo->id);
	return(0);
}
/*
	check if the m_fork is set to te id of the calling philosopher
	returns zero if any of the m_forks has the philosophers id 
*/
int fork_mask(t_philo *philo)
{
	if(philo->m_fork == philo->id || philo->next->m_fork == philo->id)
		return(0);
	return 1;
}
void *routine(void *philoarg)
{
   // struct timeval tv;
    t_philo *philo;
    
    philo = (t_philo *) philoarg;
    while(1)
    {
		if (is_dead(philo))// || philo->key->p_dead)
			break ;
		if(philo->id%philo->key->no_phil)
		{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
		}
		else
		{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
		}
		
        if(!(philo->fork) && !(philo->next->fork) && philo->rounds && fork_mask(philo))
           {
		    if(eat(philo))
				return(NULL);
		   }
			
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
    }
	// pthread_mutex_unlock(&philo->lock);
	// pthread_mutex_unlock(&philo->next->lock);
	return(NULL);
}


void ft_muteall(t_philo  *philo,int flag)
{
	int i;

	i = 0;
	//while (i++ < philo->key->no_phil)
	// {
		if (flag)
			pthread_mutex_lock(&philo->key->dlock);
		else
			pthread_mutex_unlock(&philo->key->dlock);
		philo = philo->next;
	// }
}
// int is_dead(t_philo  *philo,int no_phil)
void print_info(t_philo  *philo,int print_order)
{

	ft_putnbr(n_timestamp(&philo->life_t));
	ft_putchar(' ');
	ft_putnbr(philo->id);
	if(print_order == 1)
		ft_putstr(" has taken a fork");
	else if(print_order == 2)
		ft_putstr(" is eating");
	else if(print_order == 3)
		ft_putstr(" is sleeping");
	else if(print_order == 4)
		ft_putstr(" is thinking");
	else if(print_order == 5)
		ft_putstr(" died");
	
}
 int is_dead(t_philo  *philo)
{
	long n_time;
	int flag;

	flag = 0;
	ft_muteall(philo,1);
	if (philo->key->p_dead)
		flag =1;
	else
	{
		n_time = n_timestamp(&philo->life_t);
		if (n_time - philo->life > (philo->time_to_die))
		{
			//printf("%ld %d died \n",n_timestamp(&philo->life_t),philo->id);
			pthread_mutex_lock(&philo->key->print_lock);
			print_info(philo,5);
			pthread_mutex_unlock(&philo->key->print_lock);
			//philo->is_dead = 1;
			philo->key->p_dead = 1;
			flag =1;
		}
	}
	ft_muteall(philo,0);
	return(flag);
}
// no of phil , time to die , tte,time to sleep , number of time each philosopher should eat

int main(int argc, char *argv[]) 
{
    t_philo	*philo;
    int		i;

    philo = malloc(sizeof(t_philo) * atoi(argv[1]));
    init_philo(philo,argc, argv);
	if (atoi(argv[1]) == 1)
	{
		//put timer for time to die
		//printf("%ld %d died \n",n_timestamp(&philo[0].life_t),philo[0].id);
pthread_mutex_lock(&philo->key->print_lock);
		print_info(philo,5);
pthread_mutex_unlock(&philo->key->print_lock);
		return (0);
	}
    i = -1;
	while(++i<atoi(argv[1]))
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
    // while (1)
    // { 
	// 	i = -1;
	// 	//usleep(500);
	// 	// while (++i < atoi(argv[1]))
	// 	// {
	// 		// if (is_dead(philo,atoi(argv[1])))
	// 		// 	break ;
	// 			//kill_all(philo,atoi(argv[1]));
	// 	// }
    // }
	//printf("-- breaked --- |||");
    i = -1;
	while(++i<atoi(argv[1]))
		pthread_join(philo[i].thread, NULL);
}
