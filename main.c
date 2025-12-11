/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/11 19:53:07 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

mtx_t	serial_mtx;
#define THREAD_COUNT 10

int	run(void *arg)
{
	static	int	serial = 0;

	(void)arg;
	mtx_lock(&serial_mtx);
	printf("Thread running! %d\n", serial);
	serial++;
	mtx_unlock(&serial_mtx);
	return (0);
}
int	main(void)
{
	thrd_t	t[THREAD_COUNT];
	int		i;

	i = -1;
	if (mtx_init(&serial_mtx, mtx_plain) != thrd_success)
	{
		write(2, "Fatal error: Could not initialize mutex.\n", 41);
		return (1);
	}
	while (++i < THREAD_COUNT)
	{
		if (thrd_create(t + i, run, NULL) != thrd_success)
		{
			write(2, "Error: Coul not initialize thrd\n", 31);
			break;
		}
	}
	i = -1;
	while (++i < THREAD_COUNT)
		thrd_join(t[i], NULL);
	mtx_destroy(&serial_mtx);
}
