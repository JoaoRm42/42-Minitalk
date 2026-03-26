/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Escreve um carácter literal da format string e avança o índice.
 */
static int	print_literal(const char *s, int *i)
{
	write(1, &s[*i], 1);
	(*i)++;
	return (1);
}

/*
 * Versão bonus com parsing de flags, largura mínima e precisão.
 */
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_fmt	f;
	int		i;
	int		count;
	int		r;

	if (!format)
		return (0);
	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += print_literal(format, &i);
		else
		{
			r = ft_parse_format(format, &i, &f);
			if (r == 0)
				break ;
			count += ft_format_arg(&f, ap);
		}
	}
	va_end(ap);
	return (count);
}
