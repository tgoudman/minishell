/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:38:05 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/31 10:15:09 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd[i] != NULL)
	{
		free(cmd[i++]);
	}
	if (cmd != NULL)
		free(cmd);
}

void	free_list(t_lst **env)
{
	t_lst	*tmp;

	while (*env)
	{
		tmp = *env;
		(*env) = (*env)->next;
		free(tmp->name);
		free(tmp->data);
		free(tmp);
	}
}

void	free_list_var(t_lst_var **lst_var)
{
	t_lst_var	*tmp;

	while (*lst_var)
	{
		tmp = *lst_var;
		(*lst_var) = (*lst_var)->next;
		free(tmp->string);
		free(tmp);
	}
}
