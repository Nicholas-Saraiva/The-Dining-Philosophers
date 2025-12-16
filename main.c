/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/14 19:09:41 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	fill_table(t_table *table, char *argv[]);
static int	initialize_mutex(t_table *table);
static int	make_plato(t_philo **philos, t_table *table);
static void	free_all(t_philo **philos, t_table *table);

int	main(int argc, char *argv[])
{
	t_table	table;
	int		i;

	i = -1;
	if (!(argc == NUMBER_OF_ARGS || argc == NUMBER_OF_ARGS + 1))
		return (error_message("Error: Wrong number of args."), 1);
	if (!fill_table(&table, argv))
		return (1);
	if (!make_plato(&table.philos, &table))
		return (1);
	pthread_create(&table.thread_meal, NULL, meal_routine, &table);
	pthread_join(table.thread_meal, NULL);
	while (++i < table.n_seats)
		pthread_join(table.philos[i].thread, NULL);
	destroy_forks(&table.forks, &table);
	return (0);
}

int	fill_table(t_table *table, char *argv[])
{
	table->start_time = get_current_time_ms();
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
	table->forks = malloc(table->n_seats * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (error_message("Fatal error: Failed malloc."), 0);
	while (++i < table->n_seats)
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (error_message("Fatal error: Could not initialize mutex.") \
			, destroy_forks(&table->forks, table), 0);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (error_message("Fatal error: Could not initialize mutex.") \
	, destroy_forks(&table->forks, table), 0);
	return (1);
}

static int	make_plato(t_philo **philos, t_table *table)
{
	int	i;

	i = -1;
	*philos = malloc(table->n_seats * sizeof(t_philo));
	if (!philos)
		return (error_message("Fatal error: Failed malloc."), \
		free_all(philos, table), 0);
	while (++i < table->n_seats)
	{
		memset(&(*philos)[i], 0, sizeof(t_philo));
		if (pthread_mutex_init(&(*philos)[i].lock_seat, NULL) != 0)
			return (error_message("Fatal error: Could not initialize mutex."), \
			free_all(philos, table), 0);
		(*philos)[i].table = table;
		(*philos)[i].l_fork = &table->forks[i];
		(*philos)[i].r_fork = &table->forks[(i + 1) % table->n_seats];
		(*philos)[i].id = i;
		(*philos)[i].is_dead = 0;
		pthread_create(&(*philos)[i].thread, NULL, symposium, &(*philos)[i]);
	}
	return (1);
}

static void	free_all(t_philo **philos, t_table *table)
{
	int	i;

	i = -1;
	if ((*philos))
		while (++i < table->n_seats)
			pthread_mutex_destroy(&(*philos)->lock_seat);
	if ((*philos))
		free((*philos));
	(*philos) = NULL;
	destroy_forks(&table->forks, table);
}
