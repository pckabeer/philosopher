/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:37:32 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/22 13:46:52 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
timestamp for current time witgh the diffrence of philo started
*/
long	n_timestamp(struct timeval *time)
{
	struct timeval	n_time;

	gettimeofday(&n_time, NULL);
	return (((n_time.tv_sec - time->tv_sec) * 1000)
		+ ((n_time.tv_usec - time->tv_usec) / 1000));
}

size_t	timestamp_new(void)
{
	struct timeval	n_time;

	gettimeofday(&n_time, NULL);
	return ((n_time.tv_sec * 999990) + (n_time.tv_usec));
}

/*
	check if the m_fork is set to te id of the calling philosopher
	returns zero if any of the m_forks has the philosophers id 
*/
int	fork_mask(t_philo *philo)
{
	if (philo->m_fork == philo->id || philo->next->m_fork == philo->id)
		return (0);
	return (1);
}

void	lock_order(t_philo *philo)
{
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
}

void	ft_muteall(t_philo *philo, int lock_flag)
{
	if (lock_flag)
		pthread_mutex_lock(&philo->key->dlock);
	else
		pthread_mutex_unlock(&philo->key->dlock);
}
