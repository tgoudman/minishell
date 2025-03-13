/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:45:02 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/13 10:43:52 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_fd_infile(t_bash *shell, char *str)
{
	t_lst_fd	*tmp;

	tmp = shell->line.lst_fd;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->name) == 0)
		{
			if (tmp->type == 'i')
			{
				dup2(tmp->fd, STDIN_FILENO);
				close(tmp->fd);
				return (tmp->fd);
			}
			if (tmp->type == 'h')
			{
				tmp->fd = open(tmp->name, O_RDONLY);
				dup2(tmp->fd, STDIN_FILENO);
				close(tmp->fd);
				return (tmp->fd);
			}
		}
		tmp = tmp->next;
	}
	return (-1);
}

char	*search_infile(t_bash *shell)
{
	char		*file;
	t_lst_fd	*fd;

	file = NULL;
	fd = shell->line.lst_fd;
	if (!fd)
		return (file);
	while (fd)
	{
		if (fd->type == 'i' || fd->type == 'h')
			file = fd->name;
		fd = fd->next;
	}
	return (file);
}

int	check_cmds(t_bash *shell)
{
	pid_t	pid;

	if (shell->line.cmd_nbr == 1)
	{
		if (check_function(shell->line.cmd[0]) == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				launch_builtins(shell, 0, -1);
				shell->prev_return = 0;
				close_fd(shell);
				exit(0);
			}
			else
				waitpid(pid, NULL, 0);
			return (1);
		}
	}
	return (0);
}

int	get_fd(t_bash *shell, char *str)
{
	t_lst_fd	*tmp;

	tmp = shell->line.lst_fd;
	if (!tmp)
		return (-1);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->name) == 0)
		{
			if (tmp->type == 'o' || tmp->type == 'a')
				return (tmp->fd);
		}
		tmp = tmp->next;
	}
	return (-1);
}
