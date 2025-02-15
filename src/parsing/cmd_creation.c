/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:40:17 by jdhalv.l          #+#    #+#             */
/*   Updated: 2025/02/14 14:30:21 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_char_arg *get_lst_arg(t_lst_var *main_lst, t_cmd_pos *pos)
{
	t_lst_var	*tmp;
	t_lst_arg	*arg_stack;
	t_lst_arg	*arg_str;
	t_var		v;
	t_char_arg *args;
	
	arg_stack = NULL;
	// ft_printf(1, "start %i, char %i\n", pos->start_of_arg, pos->start_of_char);
	tmp = init_cmdarg(main_lst, pos, &v);
	while (tmp != NULL && tmp->id <= pos->end_of_arg)
	{
		move_pos_v(tmp, &v, pos);
		if (v.j == v.i && ft_strcmp(tmp->string, "") == 0)
		{
			// ft_printf(1, "%i, %i, %s\n", v.j, v.i, ft_substr(tmp->string, v.j, v.i - v.j));
			arg_str = create_new_node_arg(ft_substr(tmp->string, v.j, v.i - v.j));
			arg_str->is_space = tmp->is_space;
			list_add_back_arg(&arg_stack, arg_str);
			if (arg_str->str == NULL)
				return (free_list_arg(&arg_stack), NULL);
		}
		if (v.j < v.i)
		{
			// ft_printf(1, "%i, %i, %s\n", v.j, v.i, ft_substr(tmp->string, v.j, v.i - v.j));
			arg_str = create_new_node_arg(ft_substr(tmp->string, v.j, v.i - v.j));
			arg_str->is_space = tmp->is_space;
			list_add_back_arg(&arg_stack, arg_str);
			if (arg_str->str == NULL)
				return (free_list_arg(&arg_stack), NULL);
		// ft_printf(1, "CA string in [%i] : \033[34m \033[4m%s\033[0m\n", tmp->id, tmp->string);
		}
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	args = make_arg(arg_stack, arg_str);
	return (free_list_arg(&arg_stack), args);
}


t_lst_cmd	*get_lst_cmd(t_lst_var *main_lst, t_lst_line **line_list,
				t_lst_fd **fd_list, t_cmd_pos *pos)
{
	t_lst_var	*tmp;
	t_lst_cmd	*cmd_list;
	t_lst_line	*line;
	t_lst_fd	*fd_temp;
	int			fd_res;
	int			sbo_res;
	
	cmd_list = NULL;
	tmp = main_lst;
	fd_res = FALSE;
	if (check_cmd(&main_lst) == ERROR)
		return (NULL);
	while (tmp != NULL)
	{
		sbo_res = search_bash_op(main_lst, &cmd_list, &tmp, pos);
		if (sbo_res == CONTINUE)
			continue ;
		if (sbo_res == BREAK)
		{
			line = create_new_node_line(ft_itoa(cmd_list_count(&cmd_list)));
			list_add_back_line(line_list, line);
			break ;
		}
		if (tmp->string[pos->j] == '\0')
		{
			if (act_as_end_of_line(main_lst, &cmd_list, &tmp, pos) == TRUE)
			{
				line = create_new_node_line(ft_itoa(cmd_list_count(&cmd_list)));
				list_add_back_line(line_list, line);
			}
			continue ;
		}
		else if (is_bash_op(tmp->string[pos->j], '|'))
		{
			// ft_printf(1, "__\033[35m\033[5mPIPE\033[0m__\n");
			if (act_is_bash_op(main_lst, &cmd_list, &tmp, pos) == BREAK)
				break ;
			line = create_new_node_line(ft_itoa(cmd_list_count(&cmd_list)));
			list_add_back_line(line_list, line);
			line = create_new_node_line(ft_strdup("|"));
			list_add_back_line(line_list, line);
		}
		else if (is_bash_op(tmp->string[pos->j], '!'))
		{
			// ft_printf(1, "__\033[35m\033[5mFD\033[0m__\n");
			if (pos->i > 0 && is_bash_op(find_char(&main_lst, pos), '*') == 0)
			{
				if (exec_fd(main_lst, &cmd_list, &tmp, pos) == BREAK)
					break ;
				line = create_new_node_line(ft_itoa(cmd_list_count(&cmd_list)));
				list_add_back_line(line_list, line);
			}
			fd_res = act_is_fd(main_lst, fd_list, &tmp, pos);
			if (fd_res == ERROR)
				return (NULL);
			fd_temp = *fd_list;
			if (fd_temp != NULL)
			{
				while (fd_temp->next != NULL)
					fd_temp = fd_temp->next;
			}
			line = create_new_node_line(ft_strjoin("!", fd_temp->name));
			list_add_back_line(line_list, line);
			pos->last_type = FILE;
			if (fd_res == BREAK)
				break ;
			if (fd_res == TRUE)
			{
				line = create_new_node_line(ft_strdup("|"));
				list_add_back_line(line_list, line);
				pos->last_type = PIPE;
				if (tmp->string[pos->j] == '\0')
				{
					tmp = tmp->next;
					pos->i++;
					pos->j = 0;
					pos->start_of_arg = pos->i;
					pos->start_of_char = pos->j;
				}
			}
			pos->end_of_arg = pos->i;
			pos->end_of_char = pos->j;
		}
	}
	if (cmd_list == NULL)
		null_lst_cmd(&cmd_list);
	return (cmd_list);
}

int	cmd_parsing(t_bash *shell, t_lst_var *main_lst)
{
	t_cmd_pos		pos;
	t_lst_cmd		*cmd_list;
	t_lst_line		*line_list;
	t_lst_fd		*fd_list;

	(void)shell;
	line_list = NULL;
	fd_list = NULL;
	pos.start_of_arg = 0;
	pos.start_of_char = 0;
	pos.end_of_arg = 0;
	pos.end_of_char = 0;
	pos.last_type = FALSE;
	pos.i = 0;
	pos.j = 0;
	cmd_list = get_lst_cmd(main_lst, &line_list, &fd_list, &pos);
	free_list_var(&main_lst);
	if (cmd_list == NULL)
		return (free_list_line(&line_list), ERROR);
	create_heredoc_name(&fd_list);
	ft_printf_list_cmd(&cmd_list, 1);
	ft_printf_list_line(&line_list, 1);
	ft_printf_list_fd(&fd_list, 1);
	if (convert_lst_to_line(shell, &line_list, &cmd_list, &fd_list) == ERROR)
	{
		free_list_cmd(&cmd_list);
		free_list_line(&line_list);
		return (free_list_fd(&fd_list), ERROR);
	}
	free_list_cmd(&cmd_list);
	free_list_line(&line_list);
	return (1);
}

		// ft_printf(1, "string in [%i] : \033[34m \033[4m%s\n\033[0m", pos->i, tmp->string);
		// if (tmp->is_squote != FALSE)
		// {
		// 	pos->j = ft_strlen(tmp->string);
		// 	tmp = tmp->next;
		// 	if (tmp == NULL)
		// 		exec_create(main_lst, &cmd_list, pos);
		// 	pos->i++;
		// 	pos->j = 0;
		// 	continue ;
		// }
		// ft_printf(1, "string in [%i] : \033[34m \033[5m%c\n\033[0m", pos->i, tmp->string[pos->j]);
		// while (tmp->string[pos->j] != '\0' && is_bash_op(tmp->string[pos->j], '*') == 0)
		// 	pos->j++;