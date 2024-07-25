/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:02 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/25 23:02:12 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t				server_pid = 0;

void	send_bit(int bit)
{
	if (bit == 1)
	{
		kill(server_pid, SIGUSR1);
		pause();
	}
	if (bit == 0)
	{
		kill(server_pid, SIGUSR2);
		pause();
	}
}

void	encrypt_message(char character)
{
	int	i;
	int	bit;

	i = 8;
	while (i--)
	{
		bit = (character >> i & 1);
		send_bit(bit);
	}
}
void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		return ;
	else if (signum == SIGUSR2)
		ft_printf("Message received.");
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

int	main(int argc, char *argv[])
{
	int		i;
	char	*message;
	pid_t	client_pid;

	if (argc == 3)
	{
		i = 0;
		client_pid = getpid();
		server_pid = ft_atoi(argv[1]);
		message = argv[2];
		ft_printf("PID: %d\n", client_pid);
		setup_signal_handlers(SIGUSR1);
		setup_signal_handlers(SIGUSR2);
		while (message[i] != '\0')
		{
			encrypt_message(message[i]);
			i++;
		}
		encrypt_message('\0');
	}
	else
		ft_printf("Error: Invalid arguments\n");
}
/*
TO DO:
		//1. breakdown message string into bits and send signals accordingly
		2. create stop condition to signify end of message
		3. BONUS: once serves sends signal back print "Message received"
*/