/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/26 17:46:26 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sig	g_tracker = {0, 0};

void	decrypt_message(int bit, pid_t client_pid)
{
	g_tracker.character = (g_tracker.character << 1) | bit;
	g_tracker.count++;
	if (g_tracker.count == 8)
	{
		if (g_tracker.character == '\0')
		{
			kill(client_pid, SIGUSR2);
			ft_printf("\n");
		}
		else
			ft_printf("%c", g_tracker.character);
		g_tracker.character = 0;
		g_tracker.count = 0;
	}
	kill(client_pid, SIGUSR1);
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		decrypt_message(1, info->si_pid);
	if (signum == SIGUSR2)
		decrypt_message(0, info->si_pid);
}

void	setup_signal_handlers(int signum)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	act.sa_sigaction = handle_signal;
	sigemptyset(&act.sa_mask);
	if (sigaction(signum, &act, NULL) == -1)
		ft_printf("Error\n");
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
