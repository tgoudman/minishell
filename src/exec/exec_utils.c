/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:40:19 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/14 18:59:52 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_bash *shell);

char	*get_path(t_bash *shell, char *cmd)
{
	int		j;
	char	**all_path;
	char	*join;
	char	*exec;

	all_path = ft_split(ft_getenv(shell), ':');
	if (!all_path)
		return (NULL);
	j = 0;
	while (all_path[j])
	{
		join = ft_strjoin(all_path[j], "/");
		exec = ft_strjoin(join, cmd);
		free(join);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_cmd(all_path);
			return (exec);
		}
		free(exec);
		j++;
	}
	free_cmd(all_path);
	return (cmd);
}

int	check_function(t_cmd cmd)
{
	if (ft_strcmp(cmd.name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd.name, "exit") == 0)
		return (1);
	return (0);
}

void	launch_builtins(t_bash *shell, int index, int oldpipe)
{
	char	*outfile;

	(void)oldpipe;
	outfile = search_file(shell, index);
	if (outfile != NULL)
		redirect_fd(shell, outfile + 1);
	close_fd(shell, 0);
	single_function(shell, &shell->line.cmd[index], index, STDOUT_FILENO);
	if (shell->line.cmd_nbr > 1)
	{
		call_free(shell);
		free_list_env(shell->lst_env);
		exit (0);
	}
}

char	*ft_getenv(t_bash *shell)
{
	t_lst	*lst;

	lst = shell->lst_env;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->name && lst->data)
		{
			if (ft_strcmp("PATH", lst->name) == 0)
				return (lst->data);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	close_fd_heredocs(t_bash *shell)
{
	t_lst_fd	*lst;

	lst = shell->line.lst_fd;
	while (lst)
	{
		if (lst->fd != STDIN_FILENO && lst->fd != STDOUT_FILENO)
			close(lst->fd);
		lst = lst->next;
	}
}
