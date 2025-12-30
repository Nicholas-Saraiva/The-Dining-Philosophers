/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:44:01 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/24 18:26:13 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifdef __STDC_NO_THREADS__
#  error Please give back my THREADS sob sob ;-;
# endif

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# define NUMBER_OF_ARGS 5

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					meal_max;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					n_seats;
	long long			start_time;
	int					drinked_hemlock;
	pthread_mutex_t		print;
	pthread_mutex_t		*forks;
	t_philo				*philos;
	pthread_t			thread_meal;
}	t_table;

typedef struct s_philo
{
	int					id;
	int					meal_count;
	int					last_time_meal;
	pthread_t			thread;
	t_table				*table;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		lock_seat;
}	t_philo;

//=-=-=-= errors.c =-=-=-=
void		error_message(char *str);

//=-=-=-= utils.c =-=-=-=
int			is_numeric(char *str);
int			ft_atoi(const char *nptr);
int			ft_isspace(char c);
void		destroy_forks(pthread_mutex_t **mutex, t_table *table);
void		safe_print_thread(t_philo *philo, char *str);

//=-=-=-= time.c =-=-=-=
long long	get_current_time_ms(void);
long long	get_elapsed_time(t_table *table);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

//=-=-=-= philosophers.c =-=-=-=
void		*symposium(void *arg);
void		*meal_routine(void *arg);
void		*only_one(void *arg);

//=-=-=-= race_utils.c =-=-=-=
int			check_death(t_philo *philo);

#endif
