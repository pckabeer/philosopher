/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:35:25 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/20 11:14:22 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	t_sleep(t_philo *philo, int ttime)
{
	size_t	ts;
	size_t	target;

	ts = timestamp_new();
	target = ts + (ttime * 1000);
	while (ts < target)
	{
		if (is_dead(philo))
			return (1);
		ts = timestamp_new();
	}
	return (0);
}

int	*single_t_sleep(t_philo *philo, int ttime)
{
	size_t	ts;
	size_t	target;
	long	n_time;

	ts = timestamp_new();
	target = ts + (ttime * 1000);
	while (ts < target)
	{
		n_time = n_timestamp(&philo->life_t);
		if (n_time - philo->life > (philo->time_to_die))
		{
			ft_putnbr(n_timestamp(&philo->life_t));
			ft_putchar(' ');
			ft_putnbr(philo->id);
			ft_putstr(" died");
			return (NULL);
		}
		ts = timestamp_new();
	}
	return (NULL);
}

int	ft_sleep(t_philo *philo)
{
	size_t	ts;
	size_t	target;

	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
	ts = timestamp_new();
	target = ts + (philo->time_to_sleep * 1000);
	while (ts < target)
	{
		if (is_dead(philo))
			return (1);
		ts = timestamp_new();
	}
	if (philo->id % philo->key->no_phil)
	{
		pthread_mutex_lock(&philo->lock);
		pthread_mutex_lock(&philo->next->lock);
	}
	else
	{
		pthread_mutex_lock(&philo->next->lock);
		pthread_mutex_lock(&philo->lock);
	}
	return (0);
}

void	print_info(t_philo *philo, int print_order)
{	
	ft_muteall(philo, 1);
	pthread_mutex_lock(&philo->key->print_lock);
	pthread_mutex_lock(&philo->rlock);
	//printf("Philo %d -- is dead : %d and  rounds :%d\n",philo->id,philo->key->p_dead,philo->rounds);

	if(!philo->key->p_dead )//&& philo->rounds)// not dying ./philo 3 100 100 500 1 on mutiple tries . 
	{
		ft_putnbr(n_timestamp(&philo->life_t));
		ft_putchar(' ');
		ft_putnbr(philo->id);
		if (print_order == 1)
			ft_putstr(" has taken a fork");
		else if (print_order == 2)
			ft_putstr(" is eating");
		else if (print_order == 3)
			ft_putstr(" is sleeping");
		else if (print_order == 4)
			ft_putstr(" is thinking");
		else if (print_order == 5)
			ft_putstr(" died");
	}
	pthread_mutex_unlock(&philo->rlock);
	pthread_mutex_unlock(&philo->key->print_lock);
	ft_muteall(philo, 0);
}

int	is_dead(t_philo *philo)
{
	long	n_time;
	int		flag;
	
	flag = 0;
	ft_muteall(philo, 1);
	if (philo->key->p_dead)
		flag = 1;
	else
	{
			//printf(" -- Philo %d -- is dead : %d and  rounds :%d\n",philo->id,philo->key->p_dead,philo->rounds);

		n_time = n_timestamp(&philo->life_t);
		if (n_time - philo->life > (philo->time_to_die))
		{
			ft_muteall(philo, 0);
			print_info(philo, 5);
			ft_muteall(philo, 1);
			philo->key->p_dead = 1; 
			flag = 1;
		}
	}
	ft_muteall(philo, 0);
	return (flag);
}

void	ft_muteall(t_philo *philo, int lock_flag)
{
	if (lock_flag)
		pthread_mutex_lock(&philo->key->dlock);
	else
		pthread_mutex_unlock(&philo->key->dlock);
}
