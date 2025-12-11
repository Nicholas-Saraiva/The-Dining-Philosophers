/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:11:58 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/11 19:33:34 by nsaraiva         ###   ########.fr       */
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
	mtx_init(&serial_mtx, mtx_plain);
	while (++i < THREAD_COUNT)
		thrd_create(t + i, run, NULL);
	i = -1;
	while (++i < THREAD_COUNT)
		thrd_join(t[i], NULL);
	mtx_destroy(&serial_mtx);
}
