/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:01:21 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 14:44:41 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Imprime um número sem sinal em base 10 e devolve os bytes escritos.
 */
int	ft_printunnbr(unsigned long nbr)
{
	int	i;

	i = 0;
	if (nbr < 10)
		i += ft_singlechar(nbr + 48);
	else
	{
		i += ft_printunnbr(nbr / 10);
		i += ft_printunnbr (nbr % 10);
	}
	return (i);
}

/*
 * Imprime um número com sinal em base 10 e devolve os bytes escritos.
 */
int	ft_printnbr(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i += ft_singlechar('-');
	}
	if (nbr < 10)
		i += ft_singlechar(nbr + 48);
	else
	{
		i += ft_printnbr(nbr / 10);
		i += ft_printnbr(nbr % 10);
	}
	return (i);
}
