/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:21:14 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/10 12:02:29 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_signale(t_bash *shell, pid_t pid)
{
	int		status;
	int		signal_number;

	waitpid(pid, &status, 0);
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