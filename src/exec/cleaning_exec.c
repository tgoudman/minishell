/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:28:38 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/16 04:01:34 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(t_bash *shell)
{
	t_cmd	**cmd;
	int		i;
	int		j;

	if (!shell || !shell->line.cmd)
		return ;
	cmd = &shell->line.cmd;
	j = -1;
	while (cmd[++j] != NULL)
	{
		i = -1;
		if (cmd[j] != NULL)
		{
			if (cmd[j]->args)
			{
				while (cmd[j]->args[i])
					free(cmd[j]->args[++i]);
				free(cmd[j]->args);
			}
			if (cmd[j]->name)
				free(cmd[j]->name);
			free(cmd[j]);
		}
	}
}

void	free_cmd_exec(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		cmd[i] = NULL;
		++i;
	}
	if (cmd != NULL)
		free(cmd);
	cmd = NULL;
}

void	free_list_env(t_lst *env)
{
	t_lst	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name != NULL)
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		if (tmp->data != NULL)
		{
			free(tmp->data);
			tmp->data = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			++i;
		}
		free(tab);
	}
}
