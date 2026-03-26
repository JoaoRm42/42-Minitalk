/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Calcula zeros de precisão e espaços de padding para o número formatado.
 */
static int	get_padding(t_fmt *f, int plen, int nlen, int *zprec)
{
	int	pad;

	*zprec = 0;
	if (f->dot && f->precision > nlen)
		*zprec = f->precision - nlen;
	pad = f->width - (plen + *zprec + nlen);
	if (pad < 0)
		pad = 0;
	return (pad);
}

/*
 * Escreve prefixo, zeros e número, respeitando alinhamento e flags.
 */
static int	write_numeric(char *num, char *prefix, t_fmt *f, int nlen)
{
	int	plen;
	int	zprec;
	int	pad;
	int	out;

	plen = (int)ft_strlen_pf(prefix);
	pad = get_padding(f, plen, nlen, &zprec);
	out = 0;
	if (!f->minus && (!f->zero || f->dot))
		out += ft_putnchar(' ', pad);
	out += ft_putstrn(prefix, plen);
	if (!f->minus && f->zero && !f->dot)
		out += ft_putnchar('0', pad);
	out += ft_putnchar('0', zprec);
	if (nlen > 0)
		out += ft_putstrn(num, nlen);
	if (f->minus)
		out += ft_putnchar(' ', pad);
	return (out);
}

/*
 * Aplica a regra de precisão zero para valor zero e delega a escrita final.
 */
int	ft_print_numeric(char *num, char *prefix, t_fmt *f)
{
	int	nlen;

	nlen = (int)ft_strlen_pf(num);
	if (f->dot && f->precision == 0 && num[0] == '0' && num[1] == '\0')
		nlen = 0;
	return (write_numeric(num, prefix, f, nlen));
}
