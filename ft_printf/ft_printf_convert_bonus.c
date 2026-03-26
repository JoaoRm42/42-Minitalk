/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_convert_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Calcula quantos dígitos são necessários para representar n na base dada.
 */
static int	num_len(unsigned long long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long long)base)
	{
		n /= (unsigned long long)base;
		len++;
	}
	return (len);
}

/*
 * Converte um unsigned long long para string na base pedida.
 */
char	*ft_utoa_base(unsigned long long n, int base, int upper)
{
	char	*digits;
	char	*res;
	int		len;

	if (upper)
		digits = "0123456789ABCDEF";
	else
		digits = "0123456789abcdef";
	len = num_len(n, base);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = digits[n % (unsigned long long)base];
		n /= (unsigned long long)base;
	}
	return (res);
}
