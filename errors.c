/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaraiva <nsaraiva@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:27:07 by nsaraiva          #+#    #+#             */
/*   Updated: 2025/12/11 20:30:22 by nsaraiva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_message(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i]);
	write (2, str, i);
	write (2, "\n", 1);
}