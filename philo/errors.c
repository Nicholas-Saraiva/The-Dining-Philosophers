/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:27:07 by nsaraiva          #+#    #+#             */
/*   Updated: 2026/01/01 21:03:17 by nsaraiva         ###   ########.fr       */
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

int	fail_thread_create(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	philo->table->drinked_hemlock = 1;
	error_message("FAIL THREAD CREATION");
	pthread_mutex_unlock(&philo->table->print);
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
