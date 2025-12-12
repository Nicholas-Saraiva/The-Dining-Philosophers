/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/12 21:43:31 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	fill_table(t_table *table, char *argv[]);
static int	initialize_mutex(t_table *table);
static int	make_plato(t_philo **philos, t_table *table);

int	symposium(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (philo->table->time_to_die)
	{
		mtx_lock(philo->l_fork);
		printf ("timestamp_in_ms %d has taken a fork\n", philo->id);
		mtx_lock(philo->r_fork);
		printf ("timestamp_in_ms %d has taken a fork\n", philo->id);
		printf ("timestamp_in_ms %d is eating\n", philo->id);
		mtx_unlock(philo->r_fork);
		mtx_unlock(philo->l_fork);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philos;
	int		i;

	i = -1;
	if (!(argc == NUMBER_OF_ARGS || argc == NUMBER_OF_ARGS + 1))
		return (error_message("Error: Wrong number of args."), 1);
	if (!fill_table(&table, argv))
		return (1);
	if (!make_plato(&philos, &table))
		return (1);
	while (++i < table.n_seats)
		thrd_join(philos[i].thread, NULL);
	destroy_forks(&table);
}

int	fill_table(t_table *table, char *argv[])
{
	if (!is_numeric(argv[1]) || !is_numeric(argv[2]) || \
	!is_numeric(argv[3]) || !is_numeric(argv[4]))
		return (error_message("Wrong input. Please put all in numeric."), 0);
	if (argv[5] && !is_numeric(argv[5]))
		return (error_message("Wrong input. Please put all in numeric."), 0);
	table->n_seats = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meal_max = ft_atoi(argv[5]);
	if (!initialize_mutex(table))
		return (0);
	return (1);
}

static int	initialize_mutex(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(table->n_seats * sizeof(mtx_t));
	if (!table->forks)
		return (error_message("Fatal error: Failed malloc."), 0);
	while (++i < table->n_seats)
		if (mtx_init(&table->forks[i], mtx_plain) != thrd_success)
			return (error_message("Fatal error: Could not initialize mutex.") \
			, destroy_forks(table), 0);
	return (1);
}

static int	make_plato(t_philo **philos, t_table *table)
{
	int	i;

	i = -1;
	*philos = malloc(table->n_seats * sizeof(t_philo));
	if (!philos)
		return (error_message("Fatal error: Failed malloc."), \
		destroy_forks(table), 0);
	while (++i < table->n_seats)
	{
		(*philos)[i].table = table;
		(*philos)[i].l_fork = &table->forks[i];
		(*philos)[i].r_fork = &table->forks[(i + 1) % table->n_seats];
		(*philos)[i].id = i;
		thrd_create(&(*philos)[i].thread, symposium, &(*philos)[i]);
	}
	return (1);
}
