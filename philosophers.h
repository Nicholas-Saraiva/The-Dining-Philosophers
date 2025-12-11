# ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#ifdef __STDC_NO_THREADS__
#error Please give back my THREADS sob sob ;-;
#endif

#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#define NUMBER_OF_ARGS 5

typedef struct s_philo
{
	int	meal_count;
	int	last_time_meal;
	int	*l_fork;
	int	*r_fork;
}	t_philo;

typedef struct s_table
{
	int		meal_max;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		n_seats;
	int		*forks;
	t_philo	*philos;
}	t_table;

//=-=-=-= errors.c =-=-=-=
void	error_message(char *str);

#endif
