/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:33:07 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/14 18:09:29 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	dprintf(2, "execute cmd %s in %s index is  %d\n", cmd.name, outfile, index);
void	launch_cmd(t_bash *shell, t_cmd cmd, int index)
{
	char	**env;
	char	*path;
	char	*outfile;

	outfile = search_file(shell, index);
	if (outfile != NULL)
		redirect_fd(shell, outfile + 1);
	close_fd_heredocs(shell);
	path = get_path(shell, cmd.name);
	env = lst_to_tab(shell->lst_env);
	if (!path)
		free_cmd_path(shell, cmd, env);
	shell->prev_return = 0;
	if (execve(path, cmd.args, env) == -1)
	{
		ft_printf(2, "minishell: Command '%s' not found\n", cmd.name);
		call_free(shell);
		free_list_env(shell->lst_env);
		free_cmd_exec(env);
		free(path);
		shell->prev_return = 127;
		exit (127);
	}
}

int	do_pipe(t_bash *shell, int index_cmd, int old_fd, int *pipe_fd)
{
	pid_t	pid;
	char	*infile;

	infile = search_file_two(shell, index_cmd);
	pid = fork();
	if (pid == 0)
	{
		if (infile != NULL)
			redirect_fd_infile(shell, infile + 1);
		else if (old_fd > 0)
		{
			dup2(old_fd, STDIN_FILENO);
			close(old_fd);
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close_pipe(pipe_fd, -1);
		if (check_function(shell->line.cmd[index_cmd]) == 1)
			launch_builtins(shell, index_cmd, old_fd);
		launch_cmd(shell, shell->line.cmd[index_cmd], index_cmd);
	}
	shell->line.cmd[index_cmd].pid = pid;
	close(pipe_fd[1]);
	if (old_fd > 0)
		close(old_fd);
	return (pipe_fd[0]);
}

int	init_execve(t_bash *shell)
{
	if (shell->line.cmd_nbr == 0)
		return (0);
	if (open_fds(shell) == -1)
		return (1);
	if (shell->line.cmd_nbr == 1 && search_pipe(shell, 0) == 0)
		ft_command_one(shell, 0);
	else
		ft_execve(shell);
	close_fd(shell, 1);
	return (0);
}

int	ft_execve(t_bash *shell)
{
	int		pipe_fd[2];
	int		i;
	int		j;
	int		old_fd;

	i = -1;
	j = -1;
	old_fd = 0;
	while (++j < search_pipe(shell, 0))
	{
		pipe(pipe_fd);
		if (no_command(shell, j) == -1)
			old_fd = close_pipe(pipe_fd, old_fd);
		else
			old_fd = do_pipe(shell, ++i, old_fd, pipe_fd);
	}
	close(pipe_fd[1]);
	ft_execve_final(shell, pipe_fd, ++i, j);
	if (old_fd > 0)
		close(old_fd);
	ft_waitpid(shell, i);
	return (0);
}

int	ft_execve_final(t_bash *shell, int *pipe_fd, int i, int j)
{
	char	*infile;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		infile = search_file_two(shell, i);
		if (infile != NULL)
			redirect_fd_infile(shell, infile + 1);
		else
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
		}
		if (no_command(shell, j) == -1)
		{
			close_fd(shell, 0);
			exit (0);
		}
		launch_cmd(shell, shell->line.cmd[i], i);
	}
	shell->line.cmd[i].pid = pid;
	return (0);
}
