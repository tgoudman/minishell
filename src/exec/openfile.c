/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:59:26 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/11 10:40:54 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_inpout_output(t_bash *shell)
{
	t_lst_fd	*tmp;
	int			fd;

	init_file(shell);
	tmp = shell->line.lst_fd;
	while (tmp)
	{
		fd = 0;
		if (tmp->type == 'h')
			ft_heredoc(tmp->name, tmp->limit);
		if (tmp->type == 'a')
		{
			fd = ft_append(tmp->name);
			tmp->fd = fd;
		}	
		if (tmp->type == 'o')
			fd = ft_open_file(tmp->name, 1);
		if (tmp->type == 'i')
			fd = ft_open_file(tmp->name, 0);
		tmp->fd = fd;
		tmp = tmp->next;
	}
	ft_test(shell, fd);
}

int	ft_append(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("canno't open/creat %s\n", str);
		return (1);
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
			printf("canno't open/creat %s\n", str);
			return (1);
		}
		return (fd);
	}
	if (file == 0)
	{
		fd = open(str, O_WRONLY);
		if (fd == -1)
		{
			printf("%s : No such file or directory\n", str);
			return (1);
		}
		return (fd);
	}
	return (0);
}
void	close_fd(t_bash *shell)
{
	t_lst_fd *lst;

	lst = shell->line.lst_fd;
	while(lst)
	{
		// close(lst->name);
		lst = lst->next;
	}
}
