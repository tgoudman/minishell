/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:06:49 by tgoudman          #+#    #+#             */
/*   Updated: 2025/01/22 17:08:56 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *return_var_value(t_bash *shell, char *str, int i)
// {
// 	t_lst *node;
// 	t_lst *next;
// 	while(shell->lst_env->next != NULL)
// 	{
// 		if (ft_strcmp(shell->lst_env->next, str) == 0)
// 			return ()
// 	}
// }

// int	search_for_var(t_bash *shell)
// {
// 	int	i;

// 	i = 0;
// 	while(shell->line.cmd.args[i] == NULL)
// 	{
// 		if (shell->line.cmd.args[i][0] == '$')
// 			return_var_value(shell,
// 				ft_strchr(shell->line.cmd.args[i], '$'), i);
// 	}
// }

int parsing(t_bash *shell)
{
	// search_for_var(shell);
	single_function(shell);
	return (1);
}

int	cmd_manager(t_bash *shell, char *input)
{
	shell->line.cmd.args = ft_split(input, ' ');
	if (shell->line.cmd.args == NULL)
		return (0);
	parsing(shell);
	free(input);
	free_cmd(shell->line.cmd.args);
	return (0);
}