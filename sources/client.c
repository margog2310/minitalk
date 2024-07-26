/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:02 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/26 19:47:05 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>

volatile sig_atomic_t	g_flag = 0;

void	encrypt_message(char character, pid_t server_pid)
{
	int	i;
	int	bit;

	i = 8;
	while (i--)
	{
		bit = (character >> i & 1);
		if (bit == 1)
			kill(server_pid, SIGUSR1);
		if (bit == 0)
			kill(server_pid, SIGUSR2);
		while (1)
		{
			if (g_flag == 1)
			{
				g_flag = 0;
				break ;
			}
		}
	}
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
	{
		g_flag = 1;
		return ;
	}
	else if (signum == SIGUSR2)
		ft_printf("Message received.");
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

bool	check_pid(char *str)
{
	unsigned int	i;
	pid_t			server_pid;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	server_pid = ft_atoi(str);
	if (kill(server_pid, 0 == -1))
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	int		i;
	pid_t	server_pid;

	if (argc == 3)
	{
		i = 0;
		if (!check_pid(argv[1]))
		{
			ft_printf("Invalid PID");
			exit(EXIT_FAILURE);
		}
		server_pid = ft_atoi(argv[1]);
		setup_signal_handlers(SIGUSR1);
		setup_signal_handlers(SIGUSR2);
		while (*argv[2])
			encrypt_message(*argv[2]++, server_pid);
		encrypt_message('\0', server_pid);
	}
	else
		ft_printf("Error: Invalid arguments\n");
}
