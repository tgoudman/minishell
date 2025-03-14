/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:13 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/14 00:58:02 by nezumickey       ###   ########.fr       */
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

ssize_t	read_heredoc_line(char *buffer, size_t buffer_size)
{
	char	c;
	ssize_t	bytes_read;
	size_t	index;

	index = 0;
	write(1, "heredoc> ", 9);
	while (index < buffer_size - 1)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read == -1)
		{
			perror("read");
			return (-1);
		}
		if (bytes_read == 0)
		{
			write(1, "\n", 1);
			return (0);
		}
		buffer[index++] = c;
		if (c == '\n')
			break ;
	}
	buffer[index] = '\0';
	return (index);
}

int	ft_heredoc(char *delimiter, int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	line_size;

	while (1)
	{
		if (g_stop == 1)
			return (g_stop = 0, -1);
		line_size = read_heredoc_line(buffer, BUFFER_SIZE);
		if (line_size == -1)
			return (-1);
		if (line_size == 0)
		{
			dprintf(2, "here-document delimited by end-of-file (wanted `%s`)\n",
				delimiter);
			return (0);
		}
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
			&& buffer[strlen(delimiter)] == '\n')
			break ;
		dprintf(fd, "%s", buffer);
	}
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
