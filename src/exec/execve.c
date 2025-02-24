/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:33:07 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/24 13:27:36 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	launch_cmd(t_bash *shell, t_cmd cmd, int index)
{
	char	**env;
	char	*path;
	char	*file;

	path = get_path(shell, cmd.name);
	env = lst_to_tab(shell->lst_env);
	file = search_file(shell, index);
	if (file != NULL)
		redirect_fd(shell, file + 1);
	close_fd_heredocs(shell);
	if (execve(path, cmd.args, env) == -1)
	{
		ft_putendl_fd("command not found: ", 2);
		ft_putendl_fd(cmd.name, 2);
		free_cmd(cmd.args);
		free_cmd(env);
		exit (1);
	}
}

// printf("signal PID = %d\n", WIFSIGNALED(status));
//if signal == 0 -> SUCCESS_fork
void	do_pipe(t_bash *shell, t_cmd cmd, int index)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (ft_putendl_fd("pipe failed\n", 2));
	pid = fork();
	if (pid == 0)
	{
		close_fd(shell);
		close(pipe_fd[0]);
		if (check_function(cmd) == 1)
			launch_builtins(shell, index, pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		launch_cmd(shell, cmd, index);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}

int	init_execve(t_bash *shell)
{
	pid_t	pid;

	if (open_fds(shell) == -1)
		return (1);
	if (check_cmds(shell) == 1)
	{
		close_fd(shell);
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("fork failed\n");
		return (1);
	}
	if (pid == 0)
	{
		init_heredocs(shell);
		ft_execve(shell);
	}
	waitpid(pid, NULL, 0);
	close_fd(shell);
	return (0);
}

int	ft_execve(t_bash *shell)
{
	t_cmd	*cmd;
	char	*file;
	int		i;

	i = 0;
	cmd = shell->line.cmd;
	file = search_infile(shell);
	if (file != NULL)
		redirect_fd_infile(shell, file);
	while (shell->line.cmd_nbr > 1)
	{
		do_pipe(shell, cmd[i], i);
		shell->line.cmd_nbr--;
		++i;
	}
	launch_cmd(shell, cmd[i], i);
	wait(NULL);
	return (0);
}
