/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:33:20 by nsaraiva          #+#    #+#             */
/*   Updated: 2026/01/03 23:31:18 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

void	destroy_forks(pthread_mutex_t **mutex, t_table *table)
{
	int	i;

	i = 0;
	if (!table->forks || !(*mutex))
		return ;
	while (i < table->n_seats)
	{
		pthread_mutex_destroy(&(*mutex)[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	free((*mutex));
	(*mutex) = NULL;
}

void	safe_print_thread(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->drinked_hemlock)
	{
		pthread_mutex_unlock(&philo->table->print);
		return ;
	}
	printf ("%lld %d %s", \
get_elapsed_time(philo->table), philo->id, str);
	pthread_mutex_unlock(&philo->table->print);
}

int	init_plato(t_philo *philos, t_table *table, int i)
{
	memset(philos, 0, sizeof(t_philo));
	if (pthread_mutex_init(&philos->lock_seat, NULL) != 0)
	{
		error_message("Fatal error: Could not initialize mutex.");
		free_all(&philos, table);
		return (0);
	}
	philos->meal_count = 0;
	philos->table = table;
	philos->l_fork = &table->forks[i];
	philos->r_fork = &table->forks[(i + 1) % table->n_seats];
	philos->id = i + 1;
	if (table->n_seats > 1)
	{
		if (pthread_create(&philos->thread, NULL, \
symposium, philos) != 0)
			return (fail_thread_create(table, i));
	}
	else
		if (pthread_create(&philos->thread, NULL, only_one, philos) != 0)
			return (fail_thread_create(table, i));
	return (0);
}

int	creating_table_routine(t_table *table)
{
	if (table->n_seats > 1)
	{
		if (pthread_create(&table->thread_meal, NULL, meal_routine, table) \
!= 0)
		{
			fail_thread_create(table, table->n_seats);
			free_all(&table->philos, table);
			return (1);
		}
		pthread_join(table->thread_meal, NULL);
	}
	return (0);
}
