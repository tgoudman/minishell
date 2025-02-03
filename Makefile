# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 09:01:08 by tgoudman          #+#    #+#              #
#    Updated: 2025/02/03 15:08:53 by jdhallen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft -lreadline
OBJ_DIR = build
NAME = minishell
LIBFT_DIR = Libft

SRCS =	main.c minishell.c parsing.c signale.c \
		cleaning.c init.c init_env.c exec.c unset.c\
		builtins.c export.c echo.c variable.c ft_sep.c \
		parsing_utils.c execve.c utils.c line_creation.c \
		temp_creation.c ft_subvar.c create_temp.c\

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	echo "clean ok"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	echo "fclean ok"

re: fclean all

.PHONY: all clean fclean
