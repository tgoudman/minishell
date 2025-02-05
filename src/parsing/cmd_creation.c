/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:40:17 by jdhalv.l          #+#    #+#             */
/*   Updated: 2025/02/05 11:12:03 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	is_bash_op(char chr, char mod)
// {
// 	if (mod == '|' && (chr == '|'))
// 		return (TRUE);
// 	else if (mod == '!' && (chr == '<' || chr == '>'))
// 		return (TRUE);
// 	else if (mod == '*' && (chr == '|' || chr == '<' || chr == '>'))
// 		return (TRUE);
// 	return (FALSE);
// }

// char **cmd_create_arg(t_lst_var *main_lst, t_cmd_pos *pos)
// {
// 	t_lst_var	*tmp;
// 	t_lst_arg	*arg_stack;
// 	t_lst_arg	*arg_str;
// 	t_var		v;
// 	char 		**args;
	
// 	ft_printf(1, "start : arg[%i], lst[%i], char[%i]\nend : arg[%i], lst[%i], char[%i]\n",
// 		pos->start_of_arg,
// 		pos->start_of_char,
// 		pos->end_of_arg,
// 		pos->end_of_char);
// 	arg_stack = NULL;
// 	tmp = main_lst;
// 	while (tmp->id < pos->start_of_arg)
// 		tmp = tmp->next;
// 	v.i = pos->start_of_char;
// 	while (tmp->id <= pos->end_of_arg)
// 	{
// 		if (tmp->id != pos->start_of_arg)
// 			v.i = 0;
// 		v.j = v.i;
// 		if (pos->start_of_arg == pos->end_of_arg)
// 			v.i = pos->end_of_char;
// 		else
// 			while (tmp->string[v.i] != '\0')
// 				v.i++;
// 		ft_printf(1, "%i, %i, %s\n", pos->start_of_char, v.i, ft_substr(tmp->string, pos->start_of_char, v.i - pos->start_of_char));
// 		arg_str = create_new_node_arg(ft_substr(tmp->string, pos->start_of_char, v.i - pos->start_of_char));
// 		list_add_back_arg(&arg_stack, arg_str);
// 		if (arg_str->str == NULL)
// 			return (free_list_arg(&arg_stack), NULL);
// 		ft_printf(1, "CA string in [%i] : \033[34m \033[4m%s\033[0m\n", pos->start_of_arg, tmp->string);
// 		tmp = tmp->next;
// 		pos->start_of_char = 0;
// 		if (pos->start_of_arg == pos->end_of_arg)
// 			break;
// 		pos->start_of_arg++;
// 	}
// 	arg_str = arg_stack;
// 	v.l = 0;
// 	while (arg_str != NULL)
// 	{
// 		arg_str = arg_str->next;
// 		v.l++;
// 	}
// 	args = malloc((v.l + 1) * sizeof(char *));
// 	v.j = 0;
// 	arg_str = arg_stack;
// 	while (arg_str != NULL)
// 	{
// 		ft_printf(1, "arg count %s\n", arg_str->str);
// 		args[v.j] = ft_strdup(arg_str->str);
// 		if (args[v.j] == NULL)
// 			return (free_cmd(args), free_list_arg(&arg_stack), NULL);
// 		v.j++;
// 		arg_str = arg_str->next;
// 	}
// 	args[v.j] = NULL;
// 	ft_printf(1, "cmd : %t\n", args);
// 	free_list_arg(&arg_stack);
// 	return (args);
// }

// void	cmd_get_end_arg(t_lst_var *main_lst, t_var *v, t_cmd_pos *pos)
// {
// 	t_lst_var	*tmp;
// 	t_lst_cmd	*cmd_list;
// 	t_lst_cmd	*cmd;
// 	char **arg;
	
// 	cmd_list = NULL;
// 	tmp = main_lst;
// 	v->i = 0;
// 	while (tmp != NULL)
// 	{
// 		ft_printf(1, "string in [%i] : \033[34m \033[4m%s\n\033[0m", v->i, tmp->string);
// 		v->j = 0;
// 		if (tmp->is_squote != FALSE)
// 		{
// 			tmp = tmp->next;
// 			v->i++;
// 			continue ;
// 		}
// 		while (tmp->string[v->j] != '\0' && is_bash_op(tmp->string[v->j], '*') == 0)
// 			v->j++;
// 		if (tmp->string[v->j] == '\0')
// 		{
// 			tmp = tmp->next;
// 			v->i++;
// 			continue ;
// 		}
// 		else
// 		{
// 			pos->end_of_arg = v->i;
// 			pos->end_of_char = v->j;
// 			arg = cmd_create_arg(main_lst, pos);
// 			if (arg == NULL)
// 				return ;
// 			cmd = create_new_node_cmd(arg);
// 			ft_printf(1, "hello\n");
// 			list_add_back_cmd(&cmd_list, cmd);
// 			pos->end_of_char += 1;
// 			pos->start_of_arg = pos->end_of_arg;
// 			pos->start_of_char = pos->end_of_char;
// 		}
		
// 	}
// }

int	cmd_parsing(t_bash *shell, t_lst_var *main_lst)
{
// 	t_cmd_pos		pos;
// 	t_var 				v;

	(void)shell;
	(void)main_lst;
// 	pos.start_of_arg = 0;
// 	pos.start_of_char = 0;
// 	pos.end_of_arg = 0;
// 	pos.end_of_char = 0;
// 	cmd_get_end_arg(lst_var, len, &v, &pos);
	return (1);
}

