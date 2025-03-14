/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:29:28 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/14 00:40:15 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_function(t_bash *shell, t_cmd *cmd, int index, int fd)
{
	(void)index;
	if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (shell->func[ECHO].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (shell->func[CD].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (shell->func[PWD].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (shell->func[EXPORT].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (shell->func[UNSET].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return (shell->func[ENV].exec(shell, cmd, fd), 1);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (shell->func[EXIT].exec(shell, cmd, fd), 1);
	return (0);
}

int	ft_command_one(t_bash *shell, int index)
{
	pid_t	pid;
	char	*infile;

	if (check_function(shell->line.cmd[index]) == 1)
	{
		infile = search_infile(shell);
		if (infile != NULL)
			redirect_fd_infile(shell, infile);
		launch_builtins(shell, 0, 1);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		infile = search_infile(shell);
		if (infile != NULL)
			redirect_fd_infile(shell, infile);
		launch_cmd(shell, shell->line.cmd[index], 0);
	}
	else
		waitpid(pid, NULL, 0);
	ft_exit_signale(shell, pid);
	return (0);
}

int	no_command(t_bash *shell, int index)
{
	char	**line;
	int		i;

	i = 0;
	line = shell->line.group;
	if (line[i][0] == '0' && index == 0)
		return (ft_atoi(line[i]));
	while (index && line[i] != NULL)
	{
		if (line[i][0] == '|' && line[i] != NULL)
			index--;
		++i;
	}
	while (line[i] != NULL && line[i][0] != '|')
	{
		if (line[i][0] != '|' && line[i][0] != '!')
			return (ft_atoi(line[i]));
		++i;
	}
	return (-1);
}

int	close_pipe(int *pipe_fd, int old_fd)
{
	if (pipe_fd[1] > 0)
		close(pipe_fd[1]);
	if (old_fd > 0)
		close(old_fd);
	if (pipe_fd[0] > 0)
		close(pipe_fd[0]);
	return (-1);
}
