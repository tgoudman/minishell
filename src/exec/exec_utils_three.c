/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 07:49:44 by nezumickey        #+#    #+#             */
/*   Updated: 2025/03/10 15:26:02 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_zero_index(t_bash *shell)
{
	char		*file;
	t_line		line;
	int			i;

	i = 0;
	file = NULL;
	line = shell->line;
	while (line.group[i][0] != '0')
	{
		if (get_fd(shell, &line.group[i][1]) >= 0)
			file = line.group[i];
		if (line.group[i][0] == '|')
			file = NULL;
		++i;
	}
	while (line.group[i] != NULL && line.group[i][0] != '|')
	{
		if (line.group[i][0] == '!')
			if (get_fd(shell, &line.group[i][1]) >= 0)
				file = line.group[i];
		i++;
	}
	return (file);
}

char	*search_file(t_bash *shell, int index_cmd)
{
	char		*file;
	t_line		line;
	int			i;
	char		*index;

	i = 0;
	file = NULL;
	index = ft_itoa(index_cmd);
	line = shell->line;
	if (index_cmd == 0)
		return (free(index), search_zero_index(shell));
	while (line.group[i] != NULL
		&& ft_strcmp((const char *)line.group[i], (const char *)index) != 0)
		++i;
	while (line.group[i] != NULL && line.group[i][0] != '|')
		i--;
	++i;
	while (line.group[i] != NULL && line.group[i][0] != '|')
	{
		if (line.group[i][0] == '!')
			if (get_fd(shell, &line.group[i][1]) >= 0)
				file = line.group[i];
		i++;
	}
	return (free(index), file);
}

char	*search_zero_index_infile(t_bash *shell)
{
	char		*file;
	t_line		line;
	int			i;

	i = 0;
	file = NULL;
	line = shell->line;
	while (line.group[i] != NULL && line.group[i][0] != '|')
	{
		if (line.group[i][0] == '!')
			if (get_fd_infile(shell, &line.group[i][1]) >= 0)
				file = line.group[i];
		i++;
	}
	return (file);
}

char	*search_file_two(t_bash *shell, int index_cmd)
{
	char		*file;
	t_line		line;
	int			i;
	char		*index;

	i = 0;
	file = NULL;
	index = ft_itoa(index_cmd);
	line = shell->line;
	if (index_cmd == 0)
		return (free(index), search_zero_index_infile(shell));
	while (line.group[i] != NULL
		&& ft_strcmp((const char *)line.group[i], (const char *)index) != 0)
		i++;
	while (line.group[i] != NULL && line.group[i][0] != '|')
		i--;
	++i;
	while (line.group[i] != NULL && line.group[i][0] != '|')
	{
		if (line.group[i][0] == '!')
			if (get_fd_infile(shell, &line.group[i][1]) >= 0)
				file = line.group[i];
		i++;
	}
	return (free(index), file);
}
void	free_cmd_path(t_bash *shell, t_cmd cmd, char **env)
{
	ft_printf(2, "minishell: Command '%s' not found\n", cmd.name);
	call_free(shell);
	free_list_env(shell->lst_env);
	free_cmd_exec(env);
	shell->prev_return = 127;
	exit (127);
}
