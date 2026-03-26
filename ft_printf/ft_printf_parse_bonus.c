/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Inicializa a estrutura de formato com valores neutros.
 */
static void	init_fmt(t_fmt *f)
{
	f->minus = 0;
	f->zero = 0;
	f->dot = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
	f->width = 0;
	f->precision = 0;
	f->conv = 0;
}

/*
 * Lê as flags repetidas e ativa os respetivos campos na estrutura.
 */
static void	parse_flags(const char *s, int *i, t_fmt *f)
{
	while (s[*i] == '-' || s[*i] == '0' || s[*i] == '#'
		|| s[*i] == ' ' || s[*i] == '+')
	{
		if (s[*i] == '-')
			f->minus = 1;
		if (s[*i] == '0')
			f->zero = 1;
		if (s[*i] == '#')
			f->hash = 1;
		if (s[*i] == ' ')
			f->space = 1;
		if (s[*i] == '+')
			f->plus = 1;
		(*i)++;
	}
}

/*
 * Converte uma sequência de dígitos para inteiro e avança o índice.
 */
static int	parse_number(const char *s, int *i)
{
	int	n;

	n = 0;
	while (ft_isdigit_pf(s[*i]))
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
	}
	return (n);
}

/*
 * Processa a precisão quando encontra '.', incluindo o caso de zero explícito.
 */
static void	parse_precision(const char *s, int *i, t_fmt *f)
{
	if (s[*i] != '.')
		return ;
	f->dot = 1;
	(*i)++;
	f->precision = parse_number(s, i);
}

/*
 * Faz o parsing de um especificador completo e aplica regras de precedência.
 */
int	ft_parse_format(const char *s, int *i, t_fmt *f)
{
	(*i)++;
	if (!s[*i])
		return (0);
	init_fmt(f);
	parse_flags(s, i, f);
	f->width = parse_number(s, i);
	parse_precision(s, i, f);
	f->conv = s[*i];
	if (!f->conv)
		return (0);
	if (f->minus)
		f->zero = 0;
	if (f->plus)
		f->space = 0;
	(*i)++;
	return (1);
}
