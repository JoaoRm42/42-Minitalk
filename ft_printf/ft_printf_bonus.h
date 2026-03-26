/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/*
 * Estrutura com o estado do especificador atual no parsing do formato.
 */
typedef struct s_fmt
{
	int		minus;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	char	conv;
}	t_fmt;

/* API principal e utilitários do bonus. */
int		ft_printf(const char *format, ...);
int		ft_parse_format(const char *s, int *i, t_fmt *f);
int		ft_format_arg(t_fmt *f, va_list ap);
int		ft_print_text(char *txt, t_fmt *f);
int		ft_print_char(char c, t_fmt *f);
int		ft_print_numeric(char *num, char *prefix, t_fmt *f);
int		ft_putnchar(char c, int n);
int		ft_putstrn(char *s, int n);
size_t	ft_strlen_pf(const char *s);
int		ft_isdigit_pf(char c);
char	*ft_utoa_base(unsigned long long n, int base, int upper);
char	*ft_strdup_pf(const char *s);

#endif