/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:35:11 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/16 10:01:17 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Encaminha cada conversão para a função responsável e devolve bytes escritos.
 */
int	print_and_count(va_list args, char character)
{
	int	i;

	i = 0;
	if (character == 'c')
		i = ft_singlechar(va_arg(args, int));
	else if (character == 's')
		i = ft_printstr(va_arg(args, char *));
	else if (character == 'i' || character == 'd')
		i = ft_printnbr(va_arg(args, int));
	else if (character == 'u')
		i = ft_printunnbr(va_arg(args, unsigned int));
	else if (character == 'x')
		i = ft_printhexalow(va_arg(args, unsigned int));
	else if (character == 'X')
		i = ft_printhexaup(va_arg(args, unsigned int));
	else if (character == '%')
		i = ft_singlechar('%');
	else if (character == 'p')
		i = ft_printp(va_arg(args, unsigned long));
	else
		return (0);
	return (i);
}

/*
 * Replica o comportamento base do printf para as conversões obrigatórias.
 */
int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		bytes_in_str;
	int		i;

	i = 0;
	bytes_in_str = 0;
	va_start (args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			bytes_in_str += print_and_count (args, str[i + 1]);
			i++;
		}
		else
			bytes_in_str += ft_singlechar(str[i]);
		i++;
	}
	va_end(args);
	return (bytes_in_str);
}
