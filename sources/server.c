/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/20 21:17:18 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	int	bit;

	if (signum == SIGUSR1)
		bit = 1;
	if (signum == SIGUSR2)
		bit = 0;
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("PID: %d\n", server_pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
}
/*
TO DO:
	1. endless loop so server can constantly receive messages
	2. store received bits into a string based on signals
	3. decrypt message and print to terminal
	4. BONUS: once message is received send a signal back to client
	(UNICODE characters should be supported based on encryption method)
*/