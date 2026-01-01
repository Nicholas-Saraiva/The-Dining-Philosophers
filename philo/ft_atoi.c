/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 20:45:55 by nsaraiva          #+#    #+#             */
/*   Updated: 2026/01/01 20:46:08 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	value;

	if (!nptr)
		return (0);
	value = 0;
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (value);
		value = (value * 10) + (*nptr - '0');
		if (value > INT_MAX)
			return (-1);
		nptr++;
	}
	return (value);
}
