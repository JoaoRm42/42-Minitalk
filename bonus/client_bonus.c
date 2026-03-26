/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:21:09 by joaoped2          #+#    #+#             */
/*   Updated: 2026/03/26 00:00:00 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/* Stores ACK/BUSY flags without file-scope globals. */
static volatile sig_atomic_t	*ft_state(void)
{
	static volatile sig_atomic_t	state[2];

	return (state);
}

/* Updates local ACK/BUSY flags from server responses. */
static void	ft_confirm(int sig)
{
	if (sig == SIGUSR1)
		ft_state()[0] = 1;
	if (sig == SIGUSR2)
		ft_state()[1] = 1;
}

/* Tries to send one bit with retry while server reports BUSY. */
static int	ft_try_bit(int pid, unsigned char c, int bit)
{
	int	retries;
	int	wait_cycles;

	retries = -1;
	while (++retries <= 2000)
	{
		ft_state()[0] = 0;
		ft_state()[1] = 0;
		if (((c >> bit) & 1) && kill(pid, SIGUSR1) == -1)
			return (1);
		if (!((c >> bit) & 1) && kill(pid, SIGUSR2) == -1)
			return (1);
		wait_cycles = 0;
		while (!ft_state()[0] && !ft_state()[1] && wait_cycles++ < 2000)
			usleep(50);
		if (ft_state()[0])
			return (0);
		usleep(200);
	}
	return (1);
}

/* Sends one character bit-by-bit and retries while server is busy. */
static int	ft_send_char(int pid, unsigned char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (ft_try_bit(pid, c, bit))
			return (1);
		bit++;
	}
	return (0);
}

/* Validates input and sends a null-terminated message reliably. */
int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	struct sigaction	sa;

	i = 0;
	if (argc != 3)
		return (ft_printf("Error: wrong format\n"), ft_printf("Try: ./client"
				" <PID> <MESSAGE>\n"), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (ft_printf("Error: invalid PID\n"), 1);
	if (kill(pid, 0) == -1)
		return (ft_printf("Error: PID not available\n"), 1);
	sa.sa_handler = ft_confirm;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
		return (1);
	while (argv[2][i] != '\0' && !ft_send_char(pid, (unsigned char)argv[2][i]))
		i++;
	if (argv[2][i] != '\0' || ft_send_char(pid, '\0'))
		return (1);
	return (ft_printf("Message received by server.\n"), 0);
}
