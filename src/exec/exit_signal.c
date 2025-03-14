/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:21:14 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/14 01:05:53 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_signale(t_bash *shell, pid_t pid)
{
	int		status;
	int		signal_number;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid failed");
		shell->prev_return = 1;
		return;
	}
	if (WIFEXITED(status))
		shell->prev_return = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		shell->prev_return = 128 + signal_number;
	}
}

// fprintf(stderr, "Erreur d'exécution du programme enfant avec code 127\n");
// fprintf(stderr, "Le programme enfant a été tué signal %d\n", signal_number);