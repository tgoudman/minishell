/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_shell_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:42:51 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/10 12:12:23 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_line_to_charpp(t_bash *shell, t_lst_line **lst_line)
{
	t_lst_line	*tmp_line;
	int			line_size;
	int			i;

	line_size = 0;
	tmp_line = *lst_line;
	while (tmp_line != NULL)
	{
		tmp_line = tmp_line->next;
		line_size++;
	}
	shell->line.group = malloc((line_size + 1) * sizeof(char *));
	if (shell->line.group == NULL)
		return (free_list_line(lst_line), ERROR);
	tmp_line = *lst_line;
	i = 0;
	while (tmp_line != NULL)
	{
		shell->line.group[i] = ft_strdup(tmp_line->param);
		if (shell->line.group[i] == NULL)
			return (ERROR);
		i++;
		tmp_line = tmp_line->next;
	}
	return (shell->line.group[i] = NULL, TRUE);
}

int	give_value_to_cmd(t_bash *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->line.cmd_nbr = 0;
	while (shell->line.group[j] != NULL)
	{
		if (ft_isdigit(shell->line.group[j][0]) == 1)
			shell->line.cmd_nbr++;
		j++;
	}
	while (i < shell->line.cmd_nbr)
	{
		if (shell->line.cmd[i].args != NULL
			&& shell->line.cmd[i].args[0] != NULL)
		{
			shell->line.cmd[i].name = ft_strdup(shell->line.cmd[i].args[0]);
			if (shell->line.cmd[i].name == NULL)
				return (ERROR);
		}
		i++;
	}
	return (TRUE);
}

int	convert_lst_to_line(t_bash *shell, t_lst_line **lst_line,
		t_lst_cmd **lst_cmd, t_lst_fd **lst_fd)
{
	int	res;

	free_cmd(shell->line.group);
	if (lst_line_to_charpp(shell, lst_line) == ERROR)
		return (ERROR);
	shell->line.lst_fd = *lst_fd;
	res = lst_cmd_to_cmd_tab(shell, lst_cmd);
	if (res == ERROR)
		return (ERROR);
	if (give_value_to_cmd(shell) == ERROR)
		return (ERROR);
	return (TRUE);
}
