/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2026/01/01 21:12:23 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	fill_table(t_table *table, char *argv[]);
static int	initialize_mutex(t_table *table);
static int	make_plato(t_philo **philos, t_table *table);

int	main(int argc, char *argv[])
{
	t_table	table;
	int		i;

	i = -1;
	if (!(argc == NUMBER_OF_ARGS || argc == NUMBER_OF_ARGS + 1))
	{
		error_message("Error: Wrong number of args.");
		return (1);
	}
	if (!fill_table(&table, argv) || make_plato(&table.philos, &table))
	{
		free_all(&table.philos, &table);
		return (1);
	}
	if (creating_table_routine(&table))
		return (1);
	while (++i < table.n_seats)
		pthread_join(table.philos[i].thread, NULL);
	free_all(&table.philos, &table);
	return (0);
}

int	fill_table(t_table *table, char *argv[])
{
	table->start_time = get_current_time_ms();
	if (!is_numeric(argv[1]) || !is_numeric(argv[2]) || !is_numeric(argv[3]) \
	|| !is_numeric(argv[4]) || (argv[5] && !is_numeric(argv[5])))
	{
		error_message("Wrong input. Please put all in numeric.");
		return (0);
	}
	table->n_seats = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->n_seats == -1 || table->time_to_die == -1 || \
table->time_to_eat == -1 || table->time_to_sleep == -1)
	{
		error_message("Wrong input. Number invalid.");
		return (0);
	}
	table->drinked_hemlock = 0;
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
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			error_message("Fatal error: Could not initialize mutex.");
			destroy_forks(&table->forks, table);
			return (0);
		}
	}
	if (pthread_mutex_init(&table->print, NULL) != 0)
	{
		error_message("Fatal error: Could not initialize mutex.");
		destroy_forks(&table->forks, table);
		return (0);
	}
	return (1);
}

static int	make_plato(t_philo **philos, t_table *table)
{
	int	i;

	i = -1;
	*philos = malloc(table->n_seats * sizeof(t_philo));
	if (!(*philos))
	{
		error_message("Fatal error: Failed malloc.");
		free_all(philos, table);
		return (1);
	}
	while (++i < table->n_seats)
		if (init_plato(&(*philos)[i], table, i))
			return (1);
	return (0);
}
