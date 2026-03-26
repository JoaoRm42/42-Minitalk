/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_dispatch_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Formata inteiros com sinal, incluindo prefixos '+' e espaço.
 */
static int	format_signed(t_fmt *f, va_list ap)
{
	long long			v;
	unsigned long long	abs_v;
	char				*num;
	char				*prefix;
	int					out;

	v = (long long)va_arg(ap, int);
	prefix = "";
	if (v < 0)
		prefix = "-";
	else if (f->plus)
		prefix = "+";
	else if (f->space)
		prefix = " ";
	if (v < 0)
		abs_v = (unsigned long long)(-v);
	else
		abs_v = (unsigned long long)v;
	num = ft_utoa_base(abs_v, 10, 0);
	if (!num)
		return (0);
	out = ft_print_numeric(num, prefix, f);
	free(num);
	return (out);
}

/*
 * Formata inteiros sem sinal em base 10 ou 16, com suporte a '#'.
 */
static int	format_unsigned(t_fmt *f, unsigned long long v, int upper)
{
	char	*num;
	char	*prefix;
	int		base;
	int		out;

	prefix = "";
	base = 16;
	if (f->conv == 'u')
		base = 10;
	if ((f->conv == 'x' || f->conv == 'X') && f->hash && v != 0)
	{
		if (f->conv == 'x')
			prefix = "0x";
		else
			prefix = "0X";
	}
	num = ft_utoa_base(v, base, upper);
	if (!num)
		return (0);
	out = ft_print_numeric(num, prefix, f);
	free(num);
	return (out);
}

/*
 * Formata ponteiros como 0x... e usa "(nil)" para ponteiros nulos.
 */
static int	format_pointer(t_fmt *f, va_list ap)
{
	unsigned long long	v;
	char				*num;
	int					out;

	v = (unsigned long long)va_arg(ap, void *);
	if (v == 0)
		return (ft_print_text("(nil)", f));
	num = ft_utoa_base(v, 16, 0);
	if (!num)
		return (0);
	out = ft_print_numeric(num, "0x", f);
	free(num);
	return (out);
}

/*
 * Decide a rotina de saída conforme a conversão lida no formato.
 */
int	ft_format_arg(t_fmt *f, va_list ap)
{
	char	*s;

	if (f->conv == 'c')
		return (ft_print_char((char)va_arg(ap, int), f));
	if (f->conv == '%')
		return (write(1, "%", 1));
	if (f->conv == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		return (ft_print_text(s, f));
	}
	if (f->conv == 'd' || f->conv == 'i')
		return (format_signed(f, ap));
	if (f->conv == 'u' || f->conv == 'x' || f->conv == 'X')
		return (format_unsigned(f, va_arg(ap, unsigned int), f->conv == 'X'));
	if (f->conv == 'p')
		return (format_pointer(f, ap));
	return (0);
}
