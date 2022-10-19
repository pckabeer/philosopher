/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:35:25 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/20 02:25:05 by kpanikka         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->key->print_lock);
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
	pthread_mutex_unlock(&philo->key->print_lock);
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
		n_time = n_timestamp(&philo->life_t);
		if (n_time - philo->life > (philo->time_to_die))
		{
			print_info(philo, 5);
			philo->key->p_dead = 1;
			flag = 1;
		}
	}
	ft_muteall(philo, 0);
	return (flag);
}

void	ft_muteall(t_philo *philo, int flag)
{
	if (flag)
		pthread_mutex_lock(&philo->key->dlock);
	else
		pthread_mutex_unlock(&philo->key->dlock);
	philo = philo->next;
}
