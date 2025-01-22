/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:08:01 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/22 17:09:10 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(t_bash *shell, int output)
{
	t_lst   *tmp;
	t_lst   *new;
	char	*tmp_str;

	(void)output;
	tmp = shell->lst_env;
	shell->prev_return = 0;
	while (tmp)
	{
		tmp_str = get_name(shell->line.cmd.args[1]);
		if (ft_strcmp(tmp->name, tmp_str) == 0)
		{
			tmp->data = ft_strdup(get_data(shell->line.cmd.args[1]));
			free(tmp_str);
			return (shell->prev_return = 0, 0);
		}
		tmp = tmp->next;
		free(tmp_str);
	}
	new = create_new_node(get_data(shell->line.cmd.args[1]),
			get_name(shell->line.cmd.args[1]));
	list_add_back(shell->lst_env, new);
	return (shell->prev_return = 0, 0);
}
