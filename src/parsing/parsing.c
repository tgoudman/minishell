/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:06:49 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/16 00:02:07 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_free(t_bash *shell)
{
	int	i;

	i = 0;
	if (shell->line.cmd != NULL)
	{
		while (i < shell->line.cmd_nbr)
		{
			if (shell->line.cmd[i].name)
			{
				free(shell->line.cmd[i].name);
				shell->line.cmd[i].name = NULL;
			}
			if (shell->line.cmd[i].args)
				free_cmd(shell->line.cmd[i].args);
			i++;
		}
		if (shell->line.cmd)
			free(shell->line.cmd);
	}
	if (shell->line.group)
		free_cmd(shell->line.group);
	if (shell->line.lst_fd)
		free_list_fd(&shell->line.lst_fd);
}

int	parsing(t_bash *shell)
{
	if (parsing_split(shell) == ERROR)
		return (shell->prev_return = 2, ERROR);
	if (shell->line.group == NULL)
		return (ERROR);
	return (1);
}

int	cmd_manager(t_bash *shell, char *input)
{
	int	parsing_res;

	interactive_mode(FALSE);
	shell->line.group = NULL;
	shell->line.cmd = NULL;
	shell->line.lst_fd = NULL;
	input = input_remake(input);
	if (input != NULL)
	{
		if (search_for_quote(shell, input) == ERROR)
			return (ERROR);
		shell->line.cmd_nbr = 1;
		if (shell->line.group == NULL)
			return (0);
		free(input);
		parsing_res = parsing(shell);
		if (parsing_res != ERROR)
			init_execve(shell);
	}
	call_free(shell);
	return (0);
}
