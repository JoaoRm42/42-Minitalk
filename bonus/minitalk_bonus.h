/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:56:41 by joaoped2          #+#    #+#             */
/*   Updated: 2023/01/11 15:22:05 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include "../ft_printf/ft_printf.h"

int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif
