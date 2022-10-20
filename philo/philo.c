/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:18:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/10/20 11:12:22 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_set(t_philo *philo, int argc, char **argv )
{
	philo->fork = 0;
	philo->m_fork = 0;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&philo->lock, NULL);
	pthread_mutex_init(&philo->rlock, NULL);
	philo->key->no_phil = ft_atoi(argv[1]);
	if (argc == 6)
		philo->rounds = ft_atoi(argv[5]);
	else
		philo->rounds = -1;
}

void	init_philo(t_philo *philo, int argc, char **argv)
{
	int		i;
	t_info	*t;

	i = 0;
	t = malloc(sizeof(t_info));
	t->p_dead = 0;
	pthread_mutex_init(&t->print_lock, NULL);
	pthread_mutex_init(&t->dlock, NULL);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].key = t;
		philo[i].id = i + 1;
		init_set(&philo[i], argc, argv);
		gettimeofday(&philo[i].life_t, NULL);
		philo[i].life = n_timestamp(&philo[i].life_t);
		if (i == (ft_atoi(argv[1]) - 1))
			philo[i].next = &philo[0];
		else
			philo[i].next = &philo[i + 1];
		i++;
	}
}

int	eat(t_philo *philo)
{
	philo->fork = 1;
	philo->next->fork = 1;
	philo->m_fork = philo->id;
	philo->next->m_fork = philo->id;
	philo->life = n_timestamp(&philo->life_t);
	pthread_mutex_unlock(&philo->rlock);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->next->lock);
	print_info(philo, 1);
	print_info(philo, 1);
	print_info(philo, 2);
	pthread_mutex_lock(&philo->rlock);
	philo->rounds--;
	pthread_mutex_unlock(&philo->rlock);
	if (t_sleep(philo, philo->time_to_eat))
		return (1);
	lock_order(philo);
	philo->fork = 0;
	philo->next->fork = 0;
	print_info(philo, 3);
	if (ft_sleep(philo))
		return (1);
	print_info(philo, 4);
	pthread_mutex_lock(&philo->rlock);
	return (0);
}

void	*routine(void *philoarg)
{
	t_philo	*philo;

	philo = (t_philo *) philoarg;
	while (philo->key->no_phil == 1)
		return (single_t_sleep(philo, philo->time_to_die));
	while (1)
	{
		if (is_dead(philo))
			break ;
		lock_order(philo);
		pthread_mutex_lock(&philo->rlock);
		if (!(philo->fork) && !(philo->next->fork) && philo->rounds
			&& fork_mask(philo))
		{
			if (eat(philo))
				return (NULL);
		}
		pthread_mutex_unlock(&philo->rlock);
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->next->lock);
	}

	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	init_philo(philo, argc, argv);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_create(&philo[i].thread, NULL, routine, (void *) &philo[i]);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(philo[i].thread, NULL);
	free(philo->key);
	free(philo);
	return (0);
}
