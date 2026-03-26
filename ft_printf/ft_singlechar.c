/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlechar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:23:43 by joaoped2          #+#    #+#             */
/*   Updated: 2022/12/15 12:27:38 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Escreve um único carácter no stdout e devolve 1.
 */
int	ft_singlechar(int c)
{
	write(1, &c, 1);
	return (1);
}
