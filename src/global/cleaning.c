/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:38:05 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/15 23:46:42 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(char **cmd)
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
	{
		free(cmd);
		cmd = NULL;
	}
}

void	free_list(t_lst **env)
{
	t_lst	*tmp;

	while (*env)
	{
		tmp = *env;
		(*env) = (*env)->next;
		if (tmp->name != NULL)
			free(tmp->name);
		if (tmp->data != NULL)
			free(tmp->data);
		if (tmp != NULL)
			free(tmp);
	}
}
