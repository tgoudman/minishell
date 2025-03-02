/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:59:26 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/02 04:56:08 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_fd(t_bash *shell, char *str)
{
	t_lst_fd	*tmp;

	tmp = shell->line.lst_fd;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->name) == 0)
		{
			if (tmp->type == 'o' || tmp->type == 'a')
			{
				dup2(tmp->fd, STDOUT_FILENO);
				close(tmp->fd);
			}
		}
		tmp = tmp->next;
	}
}

int	open_fds(t_bash *shell)
{
	t_lst_fd	*tmp;
	int			fd;

	tmp = shell->line.lst_fd;
	if (!tmp)
		return (0);
	while (tmp)
	{
		fd = 0;
		if (tmp->type == 'a')
			fd = ft_append(tmp->name);
		if (tmp->type == 'o')
			fd = ft_open_file(tmp->name, 1);
		if (tmp->type == 'i')
			fd = ft_open_file(tmp->name, 0);
		if (tmp->type == 'h')
			fd = ft_heredoc(tmp->limit, tmp->name);
		if (fd == -1)
			return (-1);
		tmp->fd = fd;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_append(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			printf("Permission denied\n");
		else if (errno == ENOENT)
			printf("Aucun fichier ou dossier de ce nom\n");
		return (-1);
	}
	return (fd);
}

int	ft_open_file(char *str, int file)
{
	int	fd;

	if (file == 1)
	{
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (errno == EACCES)
				printf("Permission denied\n");
			else if (errno == ENOENT)
				printf("Aucun fichier ou dossier de ce nom\n");
			return (-1);
		}
		return (fd);
	}
	if (file == 0)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				printf("Permission denied\n");
			else if (errno == ENOENT)
				printf("Aucun fichier ou dossier de ce nom\n");
			return (-1);
		}
		return (fd);
	}
	return (0);
}

void	close_fd(t_bash *shell)
{
	t_lst_fd	*lst;

	lst = shell->line.lst_fd;
	while (lst)
	{
		if (lst->fd != STDIN_FILENO && lst->fd != STDOUT_FILENO)
			close(lst->fd);
		if (lst->type == 'h')
		{
			if (unlink(lst->name) == -1)
				ft_printf(2, "Erreur %s: canno't remove %s\n",
					strerror(errno), lst->name);
		}
		lst = lst->next;
	}
}
