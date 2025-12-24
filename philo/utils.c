/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:33:20 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/22 19:50:46 by nsaraiva         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	value;

	if (!nptr)
		return (0);
	sign = 1;
	value = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (sign * value);
		value = (value * 10) + (*nptr - '0');
		nptr++;
	}
	return (sign * value);
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
