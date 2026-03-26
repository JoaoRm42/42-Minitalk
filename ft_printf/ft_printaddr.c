/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:51:23 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 14:37:51 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Escreve um número em hexadecimal minúsculo, usado para endereços.
 */
int	ft_printaddr(unsigned long nbr)
{
	char	*hexa;
	int		count;

	count = 0;
	hexa = "0123456789abcdef";
	if (nbr < 16)
		count += ft_singlechar(hexa[nbr]);
	else if (nbr >= 16)
	{
		count += ft_printaddr(nbr / 16);
		count += ft_printaddr(nbr % 16);
	}
	return (count);
}

/*
 * Imprime um ponteiro no formato 0x... ou (nil) quando é nulo.
 */
int	ft_printp(unsigned long nbr)
{
	int	count;

	count = 0;
	if (!nbr)
		return (write(1, "(nil)", 5));
	write (1, "0x", 2);
	count += ft_printaddr(nbr);
	return (count + 2);
}
