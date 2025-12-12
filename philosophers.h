/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:44:01 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/12 21:27:42 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifdef __STDC_NO_THREADS__
#  error Please give back my THREADS sob sob ;-;
# endif

# include <stdio.h>
# include <threads.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define NUMBER_OF_ARGS 5

typedef struct s_table
{
	int		meal_max;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		n_seats;
	mtx_t	*forks;
}	t_table;

typedef struct s_philo
{
	thrd_t	thread;
	t_table	*table;
	mtx_t	*l_fork;
	mtx_t	*r_fork;
	int		id;
	int		meal_count;
	int		last_time_meal;
}	t_philo;

//=-=-=-= errors.c =-=-=-=
void	error_message(char *str);

//=-=-=-= utils.c =-=-=-=
int		is_numeric(char *str);
int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
void	destroy_forks(t_table *table);

#endif
