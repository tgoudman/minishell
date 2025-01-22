/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:38:05 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/22 12:12:09 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		free(cmd[i++]);
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
