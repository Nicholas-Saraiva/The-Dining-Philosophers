/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:56:48 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/24 18:13:51 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		philo_meal_max(t_table *table);

void	*symposium(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *) arg;
	while (!check_death(philo))
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->lock_seat);
		safe_print_thread(philo, "is eating\n");
		philo->meal_count++;
		philo->last_time_meal = get_elapsed_time(philo->table);
		pthread_mutex_unlock(&philo->lock_seat);
		usleep(philo->table->time_to_eat * 1000);
		drop_forks(philo);
		safe_print_thread(philo, "is sleeping\n");
		usleep(philo->table->time_to_sleep * 1000);
		safe_print_thread(philo, "is thinking\n");
		if (philo->table->n_seats % 2 != 0)
			usleep(500);
	}
	return (0);
}

void	death_message(t_table *table, int i)
{
	pthread_mutex_lock(&table->print);
	printf ("%lld %d died\n", \
get_elapsed_time(table), table->philos[i].id);
	table->drinked_hemlock = 1;
	pthread_mutex_unlock(&table->print);
}

void	*meal_routine(void *arg)
{
	t_table		*table;
	int			i;
	long long	time_meal;

	table = (t_table *)arg;
	while (!table->drinked_hemlock)
	{
		i = -1;
		while (++i < table->n_seats && !table->drinked_hemlock)
		{
			philo_meal_max(table);
			pthread_mutex_lock(&table->philos[i].lock_seat);
			time_meal = table->philos[i].last_time_meal;
			pthread_mutex_unlock(&table->philos[i].lock_seat);
			if (get_elapsed_time(table) - time_meal >= table->time_to_die)
				death_message(table, i);
		}
	}
	return (0);
}

static int	philo_meal_max(t_table *table)
{
	int	i;
	int	meal_count;

	meal_count = 0;
	if (table->meal_max == 0)
		return (0);
	i = -1;
	while (++i < table->n_seats)
	{
		pthread_mutex_lock(&table->philos[i].lock_seat);
		meal_count = table->philos[i].meal_count;
		pthread_mutex_unlock(&table->philos[i].lock_seat);
		if (meal_count < table->meal_max)
			return (0);
	}
	pthread_mutex_lock(&table->print);
	table->drinked_hemlock = 1;
	pthread_mutex_unlock(&table->print);
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
