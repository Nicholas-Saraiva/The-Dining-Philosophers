/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:44:24 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/24 17:38:41 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	int	poison;

	pthread_mutex_lock(&philo->lock_seat);
	poison = philo->table->drinked_hemlock;
	pthread_mutex_unlock(&philo->lock_seat);
	return (poison);
}
