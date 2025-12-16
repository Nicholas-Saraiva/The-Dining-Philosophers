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
			safe_print_thread (philo, "has taken a fork\n");
		if (pthread_mutex_lock(philo->r_fork) == 0)
			safe_print_thread (philo, "has taken a fork\n");
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork) == 0)
			safe_print_thread (philo, "has taken a fork\n");
		if (pthread_mutex_lock(philo->l_fork) == 0)
			safe_print_thread (philo, "has taken a fork\n");
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
	while (!philo->table->drinked_hemlock)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->lock_seat);
		if (!philo->table->drinked_hemlock)
		{
			safe_print_thread(philo, "is eating\n");
			usleep(philo->table->time_to_eat * 1000);
			philo->last_time_meal = get_current_time_ms();
		}
		pthread_mutex_unlock(&philo->lock_seat);
		drop_forks(philo);
		if (!philo->table->drinked_hemlock)
		{
			safe_print_thread(philo, "is sleeping\n");
			usleep(philo->table->time_to_sleep);
			safe_print_thread(philo, "is thinking\n");
		}
	}
	return (0);
}

void	*meal_routine(void *arg)
{
	t_table		*table;
	long long	time_since_last_meal;
	int			i;

	table = (t_table *)arg;
	while (!table->drinked_hemlock)
	{
		i = -1;
		while (++i < table->n_seats)
		{
			time_since_last_meal = get_elapsed_time(table) - \
			table->philos[i].last_time_meal;
			pthread_mutex_lock(&table->philos[i].lock_seat);
			if (time_since_last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->print);
				printf ("%lld %d died\n", \
				get_elapsed_time(table), table->philos->id);	
				table->drinked_hemlock = 1;
				pthread_mutex_unlock(&table->print);
				pthread_mutex_unlock(&table->philos[i].lock_seat);
				break;
			}
			pthread_mutex_unlock(&table->philos[i].lock_seat);
		}
	}

	return (0);
}
