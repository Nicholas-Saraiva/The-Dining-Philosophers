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

static int		philo_meal_max(t_table *table);

void	*symposium(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (!philo->table->drinked_hemlock)
	{
		pthread_mutex_lock(&philo->lock_seat);
		take_forks(philo);
		if (!philo->table->drinked_hemlock)
		{
			safe_print_thread(philo, "is eating\n");
			philo->last_time_meal = get_elapsed_time(philo->table);
			usleep(philo->table->time_to_eat * 1000);
			philo->meal_count++;
		}
		pthread_mutex_unlock(&philo->lock_seat);
		drop_forks(philo);
		if (!philo->table->drinked_hemlock)
		{
			safe_print_thread(philo, "is sleeping\n");
			usleep(philo->table->time_to_sleep * 1000);
			safe_print_thread(philo, "is thinking\n");
		}
	}
	return (0);
}

void	*meal_routine(void *arg)
{
	t_table		*table;
	int			i;
	int			achive_meal_max;

	achive_meal_max = 0;
	table = (t_table *)arg;
	while (!table->drinked_hemlock)
	{
		i = -1;
		while (++i < table->n_seats)
		{
			pthread_mutex_lock(&table->philos[i].lock_seat);
			philo_meal_max(table);
			if (get_elapsed_time(table) - table->philos[i].last_time_meal \
>= table->time_to_die)
			{
				pthread_mutex_lock(&table->print);
				printf ("%lld %d died\n", \
get_elapsed_time(table), table->philos[i].id);
				table->drinked_hemlock = 1;
				pthread_mutex_unlock(&table->print);
				pthread_mutex_unlock(&table->philos[i].lock_seat);
				break ;
			}
			pthread_mutex_unlock(&table->philos[i].lock_seat);
		}
	}
	return (0);
}

static int	philo_meal_max(t_table *table)
{
	int	i;

	if (table->meal_max == 0)
		return (0);
	i = -1;
	while (++i < table->n_seats)
		if (table->philos[i].meal_count < table->meal_max)
			return (0);
	table->drinked_hemlock = 1;
	return (1);
}

void	*only_one(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	printf ("%lld %d  is thinking\n", \
get_elapsed_time(philo->table), philo[0].id);
	usleep(philo->table->time_to_die * 1000);
	printf ("%lld %d  died\n", \
get_elapsed_time(philo->table), philo[0].id);
	return (arg);
}
