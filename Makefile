# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 18:08:20 by mganchev          #+#    #+#              #
#    Updated: 2024/07/25 17:38:21 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_CLIENT = client
NAME_SERVER = server

INCLUDE = ./include
LIBFT = ./libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCDIR =./sources
OBJDIR =./build

SRCS_SERVER = $(SRCDIR)/server.c
SRCS_CLIENT = $(SRCDIR)/client.c

OBJS_SERVER = $(OBJDIR)/server.o
OBJS_CLIENT = $(OBJDIR)/client.o

all: $(OBJDIR) $(NAME_SERVER) $(NAME_CLIENT)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT)/include -c $< -o $@
	
$(NAME_SERVER): $(OBJS_SERVER)
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -L$(LIBFT) $(OBJS_SERVER) -lft -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -L$(LIBFT) $(OBJS_CLIENT) -lft -o $(NAME_CLIENT)

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJDIR)

fclean:
	@make fclean -C $(LIBFT)
	@rm -rf $(OBJDIR)
	@rm -f $(NAME_SERVER)
	@rm -f $(NAME_CLIENT)

re: fclean all

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME_CLIENT) 802024 Hello!

.PHONY: all clean fclean re libft leaks