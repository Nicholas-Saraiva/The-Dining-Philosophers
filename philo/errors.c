/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:27:07 by nsaraiva          #+#    #+#             */
/*   Updated: 2026/01/03 23:30:51 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_message(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		i++;
	write (2, str, i);
	write (2, "\n", 1);
}

int	fail_thread_create(t_table *table, int fail_position)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->print);
	table->drinked_hemlock = 1;
	error_message("FAIL THREAD CREATION");
	pthread_mutex_unlock(&table->print);
	while (++i < fail_position)
		pthread_join(table->philos[i].thread, NULL);
	return (1);
}

void	free_all(t_philo **philos, t_table *table)
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
