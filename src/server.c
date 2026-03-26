/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:19:20 by joaoped2          #+#    #+#             */
/*   Updated: 2026/03/26 00:00:00 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Rejects non-active clients while one message is currently in progress. */
static int	ft_is_busy(pid_t client_pid, pid_t *active_pid)
{
	if (*active_pid == 0)
		*active_pid = client_pid;
	if (client_pid != *active_pid)
	{
		kill(client_pid, SIGUSR2);
		return (1);
	}
	return (0);
}

/* Flushes completed byte and resets message owner when '\0' is received. */
static void	ft_flush_byte(unsigned char *c, int *curr_bit, pid_t *active_pid)
{
	if (*c == '\0')
	{
		write(1, "\n", 1);
		*active_pid = 0;
	}
	else
		write(1, c, 1);
	*curr_bit = 0;
	*c = 0;
}

/* Receives one bit from the active client and rebuilds bytes. */
static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static pid_t			active_pid;
	static int				curr_bit;
	static unsigned char	c;
	pid_t					client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (ft_is_busy(client_pid, &active_pid))
		return ;
	if (signal == SIGUSR1)
		c |= (0x01 << curr_bit);
	kill(client_pid, SIGUSR1);
	curr_bit++;
	if (curr_bit == 8)
		ft_flush_byte(&c, &curr_bit, &active_pid);
}

/* Installs signal handlers and waits for incoming bits forever. */
int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
