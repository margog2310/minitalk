/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:02 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/20 21:17:22 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		message = argv[2];
	}
}
/*
TO DO:
		1. breakdown message string into bits and send signals accordingly
		2. create stop condition to signify end of message
		3. BONUS: once serves sends signal back print "Message received"
*/