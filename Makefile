# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 09:01:08 by tgoudman          #+#    #+#              #
#    Updated: 2025/02/13 10:52:51 by tgoudman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft -lreadline
OBJ_DIR = build
NAME = minishell
PARS_DIR = src/parsing
EXEC_DIR = src/exec
SRC_DIR = src/global
vpath %.c $(PARS_DIR) $(EXEC_DIR) $(SRC_DIR)
LIBFT_DIR = Libft

SRCS =	main.c \
		minishell.c  signale.c init.c init_env.c \
		cleaning.c utils.c builtins.c export.c \
		echo.c execve.c exec.c unset.c \
		parsing.c parsing_utils.c\
		cmd_creation.c cmd_creation_action.c \
		cmd_creation_utils.c\
		temp_creation.c line_creation.c\
		ft_subvar.c create_temp.c variable.c \
		create_cmd.c cleaning_parsing.c convert_lst.c\
		heredoc.c create_line.c cmd_fd_creation.c \
		list_to_shell_line.c cmd_check.c input_remake.c \
		input_remake2.c openfile.c exec_utils.c input_output.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
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
