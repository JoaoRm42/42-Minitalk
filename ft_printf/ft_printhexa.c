/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:29:31 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 13:41:37 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Imprime um unsigned int em hexadecimal com letras maiúsculas.
 */
int	ft_printhexaup(unsigned int nbr)
{
	char	*hexa;
	int		count;

	count = 0;
	hexa = "0123456789ABCDEF";
	if (nbr < 16)
		count += ft_singlechar(hexa[nbr]);
	if (nbr >= 16)
	{
		count += ft_printhexaup(nbr / 16);
		count += ft_printhexaup(nbr % 16);
	}
	return (count);
}

/*
 * Imprime um unsigned int em hexadecimal com letras minúsculas.
 */
int	ft_printhexalow(unsigned int nbr)
{
	char	*hexa;
	int		count;

	count = 0;
	hexa = "0123456789abcdef";
	if (nbr < 16)
		count += ft_singlechar(hexa[nbr]);
	if (nbr >= 16)
	{
		count += ft_printhexalow(nbr / 16);
		count += ft_printhexalow(nbr % 16);
	}
	return (count);
}
