/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:39:26 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/13 15:59:18 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_elapsed_time(t_table *table)
{
	return (get_current_time_ms() - table->start_time);
}

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
