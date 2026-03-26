/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Imprime texto com suporte a largura mínima e precisão para %s.
 */
int	ft_print_text(char *txt, t_fmt *f)
{
	int	len;
	int	pad;
	int	out;

	len = (int)ft_strlen_pf(txt);
	if (f->conv == 's' && f->dot && f->precision < len)
		len = f->precision;
	pad = 0;
	if (f->width > len)
		pad = f->width - len;
	out = 0;
	if (!f->minus)
		out += ft_putnchar(' ', pad);
	out += ft_putstrn(txt, len);
	if (f->minus)
		out += ft_putnchar(' ', pad);
	return (out);
}

/*
 * Imprime um carácter com padding à esquerda ou à direita.
 */
int	ft_print_char(char c, t_fmt *f)
{
	int		pad;
	int		out;
	char	pc;

	pc = ' ';
	if (!f->minus && f->zero)
		pc = '0';
	pad = 0;
	if (f->width > 1)
		pad = f->width - 1;
	out = 0;
	if (!f->minus)
		out += ft_putnchar(pc, pad);
	out += write(1, &c, 1);
	if (f->minus)
		out += ft_putnchar(' ', pad);
	return (out);
}
