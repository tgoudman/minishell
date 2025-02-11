/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:13:49 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/11 15:17:48 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_type(t_lst_var **tmp, t_cmd_pos *pos, char *type)
{
	ft_printf(1, "%c\n", (*tmp)->string[pos->j]);
	if ((*tmp)->string[pos->j] == '>' && (*tmp)->string[pos->j + 1] == '>')
		*type = 'a';
	else if ((*tmp)->string[pos->j] == '<' && (*tmp)->string[pos->j + 1] == '<')
		*type = 'h';
	else if ((*tmp)->string[pos->j] == '<')
		*type = 'i';
	else if ((*tmp)->string[pos->j] == '>')
		*type = 'o';
	if (*type == 'a' || *type == 'h')
		pos->j += 2;
	else
		pos->j += 1;
	pos->start_of_arg = pos->i;
	pos->start_of_char = pos->j;
	if ((*tmp)->string[pos->j] == '\0')
	{
		*tmp = (*tmp)->next;
		if (*tmp == NULL)
			return (ft_printf(1, "minishell : syntax error heredoc\n"), BREAK);
		pos->i++;
		pos->j = 0;
		pos->start_of_arg = pos->i;
		pos->start_of_char = pos->j;
	}
	return (CONTINUE);
}

t_lst_var	*init_cmdfd(t_lst_var *m_lst, t_cmd_pos *pos)
{
	t_lst_var	*tmp;
	
	// ft_printf(1, "start : arg[%i], char[%i]\nend : arg[%i], char[%i]\n",
	// 	pos->start_of_arg,
	// 	pos->start_of_char,
	// 	pos->end_of_arg,
	// 	pos->end_of_char);
	tmp = m_lst;
	while (tmp->id < pos->start_of_arg)
		tmp = tmp->next;
	// ft_printf(1, "%s\n", tmp->string);
	return (tmp);
}

char *get_lst_fd(t_lst_var *main_lst, t_cmd_pos *pos, char *type, char **limit)
{
	t_lst_var	*tmp;
	char		*name;
	char		*temp;
	char		*temp2;
	
	tmp = init_cmdfd(main_lst, pos);
	name = ft_strdup("");
	if (name == NULL)
		return (NULL);
	if (check_file_type(&tmp, pos, type) == BREAK)
		return (NULL);
	while (tmp != NULL)
	{
		if (pos->j > 0 && is_bash_op(tmp->string[pos->j - 1], '!') == 0)
			pos->j = 0;
		while (tmp->string[pos->j] != '\0' && is_bash_op(tmp->string[pos->j], '*') == 0)
		{
			temp = ft_substr(tmp->string, pos->j, 1);
			if (temp == NULL)
				return (NULL);
			temp2 = ft_strdup(name);
			if (temp2 == NULL)
				return (NULL);
			free(name);
			name = ft_strjoin(temp2, temp);
			if (name == NULL)
				return (NULL);
			free(temp);
			free(temp2);
			pos->j++;
		}
		if (is_bash_op(tmp->string[pos->j], '*') == 1)
		{
			if (pos->j != 0)
				pos->j -= 1;
			break ;
		}
		if (tmp->next != NULL)
		{
			if (tmp->is_squote == tmp->next->is_squote)
			{
				tmp = tmp->next;
				pos->i++;
				pos->j = 0;
				break ;
			}
		}
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
		pos->i++;
	}
	pos->start_of_arg = pos->i;
	pos->start_of_char = pos->j;
	*limit = NULL;
	if (*type == 'h')
	{
		*limit = name;
		name = ft_strdup("");
	}
	return (name);
}

int	fd_create(t_lst_var *main_lst, t_lst_fd	**fd_list, t_cmd_pos *pos)
{
	t_lst_fd	*fd;
	char	*name;
	char	type;
	char	*limit;

	name = get_lst_fd(main_lst, pos, &type, &limit);
	if (name == NULL)
		return (ERROR);
	fd = create_new_node_fd(name, type, limit);
	list_add_back_fd(fd_list, fd);
	return (TRUE);
}

int	act_is_fd(t_lst_var *main_lst, t_lst_fd **fd_list,
		t_lst_var **tmp, t_cmd_pos *pos)
{
	if (fd_create(main_lst, fd_list, pos) == ERROR)
		return (ERROR);
	while ((*tmp)->id < pos->i)
	{
		*tmp = (*tmp)->next;
		if (*tmp == NULL)
			return (BREAK);
		pos->j = 0;
	}
	if (is_bash_op((*tmp)->string[pos->j], '|') == 1)
		return (pos->j++, TRUE);
	if ((*tmp)->string[pos->j] == '\0')
	{
		// ft_printf(1, "%s\n", (*tmp)->string);
		*tmp = (*tmp)->next;
		if (*tmp == NULL)
			return (BREAK);
		pos->i++;
		pos->j = 0;
	}
	if (is_bash_op((*tmp)->string[pos->j], '|') == 1)
		return (pos->j++, TRUE);
	return (0);
}

int	exec_fd(t_lst_var *main_lst, t_lst_cmd **cmd_list,
		t_lst_var **tmp, t_cmd_pos *pos)
{
	exec_create(main_lst, cmd_list, pos);
	if ((*tmp)->string[pos->j] == '\0')
	{
		*tmp = (*tmp)->next;
		if (*tmp == NULL)
			return (BREAK);
		pos->i++;
		pos->j = 0;
	}
	pos->start_of_arg = pos->i;
	pos->start_of_char = pos->j;
	return (GO_ON);
}

int	create_heredoc_name(t_lst_fd **fd_list)
{
	t_lst_fd	*fd_tmp;
	int			i;

	fd_tmp = *fd_list;
	i = 0;
	while (fd_tmp != NULL)
	{
		fd_tmp = fd_tmp->next;
	}
	return (TRUE);
}

//echo $USER<file1|echo $USER