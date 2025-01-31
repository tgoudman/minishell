/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:33:07 by tgoudman          #+#    #+#             */
/*   Updated: 2025/01/30 18:41:33 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd)
{
	int		j;
	char	**all_path;
	char	*join;
	char	*exec;

	all_path = ft_split(getenv("PATH"), ':');
	if (!all_path)
		exit(1);
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

int	launch_cmd(t_bash *shell, t_cmd *cmd)
{
	char	**s_cmd;
	char	**env;
	char	*path;

	s_cmd = join_tab(shell->line.cmd->args, ft_split(cmd->name, ' '));
	if (!s_cmd)
	{
		ft_putendl_fd("invalid command", 2);
		return (1);
	}
	path = get_path(cmd->name);
	env = lst_to_tab(shell->lst_env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putendl_fd("command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		free_cmd(s_cmd);
		return (1);
	}
	free_cmd(s_cmd);
	return (0);
}

// printf("signal PID = %d\n", WIFSIGNALED(status));
//if signal == 0 -> SUCCESS_fork
int	ft_execve(t_bash *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_fd("pipe failed\n", 2);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		launch_cmd(shell, cmd);
	else
		waitpid(pid, &status, 0);
	return (0);
}
