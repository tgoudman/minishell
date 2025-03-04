/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:33:07 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/04 11:41:26 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//DEBUG printf("file is %s with index %d cmd 
//== %s\n", infile, index, shell->line.cmd[index].name);
// free_list_fd(shell->line.lst_fd);
void	launch_cmd(t_bash *shell, t_cmd cmd, int index)
{
	char	**env;
	char	*path;
	char	*outfile;
	char	*infile;

	infile = search_file_two(shell, index);
	if (infile != NULL)
		redirect_fd_infile(shell, infile + 1);
	outfile = search_file(shell, index);
	if (outfile != NULL)
		redirect_fd(shell, outfile + 1);
	close_fd_heredocs(shell);
	path = get_path(shell, cmd.name);
	env = lst_to_tab(shell->lst_env);
	shell->prev_return = 0;
	if (execve(path, cmd.args, env) == -1)
	{
		ft_printf(2, "minishell: Command '%s' not found\n", cmd.name);
		free_list_env(shell->lst_env);
		free_tab(env);
		free_tab(shell->line.group);
		free(path);
		shell->prev_return = 127;
		exit (127);
	}
}

// printf("signal PID = %d\n", WIFSIGNALED(status));
//if signal == 0 -> SUCCESS_fork
int	do_pipe(t_bash *shell, int index, int old_fd, int *pipe_fd)
{
	pid_t	pid;
	char	*infile;

	infile = search_file_two(shell, index);
	pid = fork();
	if (pid == 0)
	{
		if (infile != NULL)
			redirect_fd_infile(shell, infile + 1);
		else if (old_fd)
		{
			dup2(old_fd, STDIN_FILENO);
			close(old_fd);
		}
		if (check_function(shell->line.cmd[index]) == 1)
			launch_builtins(shell, index, pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		launch_cmd(shell, shell->line.cmd[index], index);
	}
	close(pipe_fd[1]);
	if (old_fd)
		close(old_fd);
	return (pipe_fd[0]);
}

int	search_pipe(t_bash *shell, int nbr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->line.group[i] != NULL)
	{
		ft_printf(1, "HELLO : %s\n", shell->line.group[i]);
		if (ft_atoi(shell->line.group[i]) == nbr)
		{
			while (shell->line.group[i] != NULL &&
				shell->line.group[i][0] != '|')
				i++;
			if (shell->line.group[i] == NULL)
				return (FALSE);
			if (shell->line.group[i][0] == '|')
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	init_execve(t_bash *shell)
{
	if (open_fds(shell) == -1)
		return (1);
	if (search_pipe(shell, 0) == FALSE)
		if (check_cmds(shell) == 1)
		{
			close_fd(shell);
			return (0);
		}
	ft_printf(1, "EXEC %i \n", search_pipe(shell, 0));
	if (shell->line.cmd_nbr == 1 && search_pipe(shell, 0) == FALSE)
		ft_command_one(shell, 0);
	else
		ft_execve(shell);
	close_fd(shell);
	return (0);
}

int	ft_execve(t_bash *shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	pid_t	childpid;
	int		i;
	int		old_fd;

	old_fd = 0;
	i = -1;
	ft_printf(1, "EXEC\n");
	while (search_pipe(shell, ++i) == TRUE)// while (++i < shell->line.cmd_nbr -1)
	{
		ft_printf(1, "%i\n", search_pipe(shell, i));
		pipe(pipe_fd);
		old_fd = do_pipe(shell, i, old_fd, pipe_fd);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		launch_cmd(shell, shell->line.cmd[i], i);
	}
	childpid = waitpid(pid, &status, 0);
	if (childpid == -1)
	{
		perror("waitpid");
		exit(127);
	}
	close(old_fd);
	return (0);
}

int	ft_command_one(t_bash *shell, int index)
{
	pid_t	pid;
	char	*infile;

	infile = search_infile(shell);
	pid = fork();
	if (pid == 0)
	{
		if (infile != NULL)
			redirect_fd_infile(shell, infile);
		if (check_function(shell->line.cmd[index]) == 1)
			launch_builtins(shell, 0, 1);
		launch_cmd(shell, shell->line.cmd[index], 0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

// void print_open_fds(const char *where)
// {
// 	int	fd;

// 	fd = 0;
// 	while (fd < 10)
// 	{
// 		if (fcntl(fd, F_GETFD) != -1) 
// 			dprintf(2, "%s - FD %d is open (PID: %d)\n", where, fd, getpid());
// 		fd++;
// 	}
// }