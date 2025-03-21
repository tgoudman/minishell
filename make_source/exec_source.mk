# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    exec_source.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 14:19:42 by jdhallen          #+#    #+#              #
#    Updated: 2025/03/07 07:53:17 by nezumickey       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC_DIR = src/exec

SRCS_EXEC = builtins.c export.c heredoc.c ft_exit.c\
		echo.c execve.c exec.c unset.c ft_cd.c \
		openfile.c exec_utils.c \
		input_output.c cleaning_exec.c \
		exit_signal.c exec_utils_two.c \
		exec_utils_three.c