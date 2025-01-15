# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 09:01:08 by tgoudman          #+#    #+#              #
#    Updated: 2025/01/15 13:31:23 by tgoudman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT)
LFLAGS = -L$(LIBFT) -lft
SRCS = main.c minishell.c parsing.c
LIBFT = libft

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT)
	$(CC) $(OBJ) $(LFLAGS) $(CFLAGS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ:.o=.d)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME) 
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all
