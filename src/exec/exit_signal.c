/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:21:14 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/14 17:31:05 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpid(t_bash *shell, int nb)
{
	int		status;
	int		signal_number;
	int		i;

	i = -1;
	while (++i < nb)
	{
		if (shell->line.cmd[i].pid > 0)
		{
			if (waitpid(shell->line.cmd[i].pid, &status, 0) == -1)
			{
				perror("waitpid failed");
				shell->prev_return = 1;
				return ;
			}
		}
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