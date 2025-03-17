/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:13 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/17 13:06:39 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_heredocs(char *delimiter, char *str)
{
	int	fd;

	interactive_mode_heredocs(TRUE);
	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror("Erreur lors de l'ouverture du fichier"), -1);
	if (ft_heredoc(delimiter, fd) == -1)
	{
		close(fd);
		unlink(str);
		interactive_mode_heredocs(FALSE);
		return (-1);
	}
	interactive_mode_heredocs(FALSE);
	close(fd);
	return (fd);
}

int	ft_heredoc(char *delimiter, int fd)
{
	char	*line;
	char	*line_trim;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (g_stop == 1)
			return (free(line), g_stop = 0, -1);
		if (!line)
		{
			dprintf(2, "here-document delimited by EOF %s\n", delimiter);
			return (free(line), 0);
		}
		if (line[0] == '\n')
			continue ;
		line_trim = ft_strtrim(line, "\n");
		if (ft_strcmp(line_trim, delimiter) == 0)
			return (free(line), free(line_trim), 0);
		free(line_trim);
		dprintf(fd, "%s", line);
		free(line);
	}
	free(line);
	return (0);
}

int	get_cmd(t_bash	*shell, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->line.group[i] != NULL)
	{
		if (shell->line.group[i][0] == '|')
			++count;
		if (ft_strcmp(shell->line.group[i] + 1, str) == 0)
			return (count);
		i++;
	}
	return (count);
}

void	ft_execve_heredocs(t_bash *shell, char *str)
{
	int		i;
	int		pipe_fd[2];

	i = get_cmd(shell, str) - 1;
	if (pipe(pipe_fd) == -1)
		return (ft_putendl_fd("pipe failed\n", 2));
	while (++i < shell->line.cmd_nbr -1)
	{
		if (fork() == 0)
		{
			close_fd_heredocs(shell);
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		else
		{
			wait(NULL);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
		}
	}
}
