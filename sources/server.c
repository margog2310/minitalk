/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/25 23:05:10 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t					client_pid = 0;

void	decrypt_message(int bit)
{
	static int	count = 0;
	static int	character = 0;

	character = (character << 1) | bit;
	count++;
	if (count == 8)
	{
		if (character == '\0')
		{
			kill(client_pid, SIGUSR2);
			ft_printf("\n");
		}
		else
			ft_printf("%c", character);
		character = 0;
		count = 0;
	}
	kill(client_pid, SIGUSR1);
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	client_pid = info->si_pid;
	if (signum == SIGUSR1)
		decrypt_message(1);
	else if (signum == SIGUSR2)
		decrypt_message(0);
}

struct sigaction	setup_signal_handlers(int signum)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	act.sa_sigaction = handle_signal;
	sigemptyset(&act.sa_mask);
	if (sigaction(signum, &act, NULL) == -1)
		ft_printf("Error\n");
	return (act);
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("PID: %d\n", server_pid);
	setup_signal_handlers(SIGUSR1);
	setup_signal_handlers(SIGUSR2);
	while (1)
		pause();
}
/*
TO DO:
	//1. endless loop so server can constantly receive messages
	2. store received bits into a string based on signals
	3. decrypt message and print to terminal
	4. BONUS: once message is received send a signal back to client
	(UNICODE characters should be supported based on encryption method)
*/