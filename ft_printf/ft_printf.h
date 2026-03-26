/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:25:11 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 14:42:42 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <stddef.h>
# include <ctype.h>
# include <stdarg.h>
# include <stdint.h>

/* Funções do mandatory. */
int			ft_printf(const char *format, ...);
int			ft_singlechar(int c);
int			ft_printstr(char *str);
int			ft_printnbr(long nbr);
int			ft_printaddr(unsigned long nbr);
int			ft_printunnbr(unsigned long nbr);
int			ft_printhexalow(unsigned int nbr);
int			ft_printhexaup(unsigned int nbr);
int			ft_printp(unsigned long nbr);

#endif