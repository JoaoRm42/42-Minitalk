/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:28:39 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 12:34:12 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Imprime uma string C; quando recebe NULL escreve "(null)".
 */
int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
	}
	else
		return (write(1, "(null)", 6));
	return (i);
}
