/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:56:48 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/14 19:16:49 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->l_fork) == 0)
			printf ("%llu %d has taken a fork\n", \
				get_elapsed_time(philo->table), philo->id);
		if (pthread_mutex_lock(philo->r_fork) == 0)
			printf ("%llu %d has taken a fork\n", \
				get_elapsed_time(philo->table), philo->id);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) == 0)
			printf ("%llu %d has taken a fork\n", \
				get_elapsed_time(philo->table), philo->id);
		if (pthread_mutex_lock(philo->l_fork) == 0)
			printf ("%llu %d has taken a fork\n", \
				get_elapsed_time(philo->table), philo->id);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	*symposium(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (!philo->is_dead)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->lock_seat);
		if (!philo->is_dead)
		{
			printf ("%lld %d is eating\n", \
			get_elapsed_time(philo->table), philo->id);
			usleep(philo->table->time_to_eat * 1000);
			philo->last_time_meal = get_current_time_ms();
		}
		pthread_mutex_unlock(&philo->lock_seat);
		drop_forks(philo);
		if (!philo->is_dead)
		{
			printf ("%lld %d is sleeping\n", \
			get_elapsed_time(philo->table), philo->id);
			usleep(philo->table->time_to_sleep);
			printf ("%lld %d is thinking\n", \
			get_elapsed_time(philo->table), philo->id);
		}
	}
	return (0);
}

void	*meal_routine(void *arg)
{
	t_table		*table;
	long long	time_since_last_meal;
	int			n_death;
	int			i;

	n_death = 0;
	table = (t_table *)arg;
	while (n_death != table->n_seats)
	{
		i = -1;
		while (++i < table->n_seats)
		{
			if (table->philos[i].is_dead)
				continue ;
			time_since_last_meal = get_elapsed_time(table) - \
			table->philos[i].last_time_meal;
			if (time_since_last_meal > table->time_to_die)
			{
				printf ("%lld %d died\n", get_elapsed_time(table), \
				table->philos[i].id);
				table->philos[i].is_dead = 1;
				n_death++;
			}
		}
	}
	return (0);
}
