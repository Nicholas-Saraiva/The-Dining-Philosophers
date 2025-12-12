/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/12 20:57:12 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fill_table(t_table *table, char *argv[]);

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!(argc == NUMBER_OF_ARGS || argc == NUMBER_OF_ARGS + 1))
		return (error_message("Error: Wrong number of args."), 1);
	if (!fill_table(&table, argv))
		return (1);
	destroy_mutex(&table);
}

int	initialize_mutex(t_table *table)
{
	int	i;

	i = -1;
	if (!table->forks)
		return (error_message("Fatal error: Failed malloc."), 0);
	while (++i < table->n_seats)
		if (mtx_init(&table->forks[i], mtx_plain) != thrd_success)
			return (error_message("Fatal error: Could not initialize mutex.") \
			, destroy_mutex(table), 0);
	return (1);
}

int	fill_table(t_table *table, char *argv[])
{
	if (!is_numeric(argv[0]) || !is_numeric(argv[1]) || \
	!is_numeric(argv[2]) || !is_numeric(argv[3]))
		return (error_message("Wrong input. Please put all in numeric."), 0);
	if (argv[4] && !is_numeric(argv[4]))
		return (error_message("Wrong input. Please put all in numeric."), 0);
	table->n_seats = ft_atoi(argv[0]);
	table->time_to_die = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[3]);
	table->meal_max = ft_atoi(argv[4]);
	if (!initialize_mutex(table))
		return (0);
	return (1);
}
