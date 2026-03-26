/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Escreve o mesmo carácter n vezes e devolve o total de bytes escritos.
 */
int	ft_putnchar(char c, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
		count += write(1, &c, 1);
	return (count);
}

/*
 * Escreve até n caracteres de uma string válida.
 */
int	ft_putstrn(char *s, int n)
{
	if (!s || n <= 0)
		return (0);
	return (write(1, s, n));
}

/*
 * Mede o comprimento de uma string; devolve 0 para ponteiro nulo.
 */
size_t	ft_strlen_pf(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/*
 * Verifica se o carácter é um dígito decimal.
 */
int	ft_isdigit_pf(char c)
{
	return (c >= '0' && c <= '9');
}

/*
 * Duplica uma string para memória dinâmica.
 */
char	*ft_strdup_pf(const char *s)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(ft_strlen_pf(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
