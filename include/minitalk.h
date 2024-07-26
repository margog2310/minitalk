/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:09:09 by mganchev          #+#    #+#             */
/*   Updated: 2024/07/26 17:44:50 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# define _DEFAULT_SOURCE

# include "libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>

typedef struct s_sig
{
	volatile sig_atomic_t	character;
	volatile sig_atomic_t	count;
}							t_sig;

#endif