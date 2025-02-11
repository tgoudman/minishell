/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_shell_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:42:51 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/11 14:47:24 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_line_to_charpp(t_bash *shell, t_lst_line **lst_line)
{
	t_lst_line *tmp_line;
	int			line_size;
	int			i;

	line_size = 0;
	tmp_line = *lst_line;
	while (tmp_line != NULL)
	{
		tmp_line = tmp_line->next;
		line_size++;
	}
	free_cmd(shell->line.group);
	shell->line.group = malloc((line_size + 1) * sizeof(char *));
	if (shell->line.group == NULL)
		return (free_list_line(lst_line), ERROR);
	tmp_line = *lst_line;
	i = 0;
	while (tmp_line != NULL)
	{
		shell->line.group[i] = ft_strdup(tmp_line->param);
		if (shell->line.group[i] == NULL)
			return (ERROR);
		i++;
		tmp_line = tmp_line->next;
	}
	return (shell->line.group[i] = NULL, TRUE);
}

t_lst_arg *ft_new_cmd(t_lst_cmd *tmp_cmd, int *len)
{
	t_lst_arg	*arg_lst;
	t_lst_arg	*arg;
	t_var		v;
	char		*temp_char;
	char		*tmp;

	arg_lst = NULL;
	v.i = 0;
	v.j = 0;
	while (tmp_cmd->arg[v.i].str != NULL)
	{
		temp_char = ft_strdup("");
		if (temp_char == NULL)
			return (free_list_arg(&arg_lst), NULL);
		if	(tmp_cmd->arg[v.i].is_space == FALSE)
		{
			while (tmp_cmd->arg[v.i].is_space == FALSE)
			{
				tmp = temp_char;
				temp_char = ft_strjoin(tmp, tmp_cmd->arg[v.i].str);
				// ft_printf(1, "%s\n", temp_char);
				free(tmp);
				v.i++;
			}
			tmp = temp_char;
			temp_char = ft_strjoin(tmp, tmp_cmd->arg[v.i].str);
			free(tmp);
			if (temp_char == NULL)
				return (NULL);
		}
		else
		{
			tmp = temp_char;
			temp_char = ft_strdup(tmp_cmd->arg[v.i].str);
			if (temp_char == NULL)
				return (NULL);
			free(tmp);
		}
		arg = create_new_node_arg(ft_strdup(temp_char));
		list_add_back_arg(&arg_lst, arg);
		free(temp_char);
		v.i++;
		v.j++;
	}
	(*len) = v.j;
	return (arg_lst);
}

char	**get_charpp_cmd(t_lst_cmd *tmp_cmd)
{
	t_lst_arg	*arg_lst;
	t_lst_arg	*arg;
	char		**args;
	int			len;
	int			i;
	
	len = 0;
	// ft_printf(1,"hello\n");
	arg_lst = ft_new_cmd(tmp_cmd, &len);
	if (arg_lst == NULL)
		return (NULL);
	args = malloc((len + 1) * sizeof(char *));
	i = 0;
	arg = arg_lst;
	while (arg != NULL)
	{
		args[i] = ft_strdup(arg->str);
		if (args[i] == NULL)
			return (free_cmd(args), free_list_arg(&arg_lst), NULL);
		i++;
		arg = arg->next;
	}
	free_list_arg(&arg_lst);
	return (args[len] = NULL, args);
}

int	lst_cmd_to_cmd_tab(t_bash *shell, t_lst_cmd **lst_cmd)
{
	t_lst_cmd	*tmp_cmd;
	int			cmd_size;
	int			i;

	cmd_size = 0;
	tmp_cmd = *lst_cmd;
	if (tmp_cmd->arg == NULL && tmp_cmd->next == NULL)
		return (shell->line.cmd = NULL, TRUE);
	while (tmp_cmd != NULL)
	{
		tmp_cmd = tmp_cmd->next;
		cmd_size++;
	}
	shell->line.cmd = malloc((cmd_size + 1) * sizeof(t_cmd));
	if (shell->line.group == NULL)
		return (ERROR);
	i = 0;
	tmp_cmd = *lst_cmd;
	while (tmp_cmd != NULL)
	{
		shell->line.cmd[i].args = get_charpp_cmd(tmp_cmd);
		if (shell->line.cmd[i].args == NULL)
			return (ERROR);
		shell->line.cmd[i].input = STDIN_FILENO;
		shell->line.cmd[i].output = STDOUT_FILENO;
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	return (TRUE);
}

int	convert_lst_to_line(t_bash *shell, t_lst_line **lst_line,
		t_lst_cmd **lst_cmd, t_lst_fd **lst_fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf(1, "_____%sPARSING_RESULT%s____\n", ORG, NTL);
	if (lst_line_to_charpp(shell, lst_line) == ERROR)
		return (ERROR);
	shell->line.lst_fd = *lst_fd;
	ft_printf_list_fd(&shell->line.lst_fd, 1);
	ft_printf(1, "LINE : %s%t%s\n", YLW, shell->line.group, NTL);
	if (lst_cmd_to_cmd_tab(shell, lst_cmd) == ERROR)
		return (ERROR);
	shell->line.cmd_nbr = 0;
	while (shell->line.group[j] != NULL)
	{
		if (ft_isdigit(shell->line.group[j][0]) == 1)
			shell->line.cmd_nbr++;
		j++;
	}
	ft_printf(1, "CMD NBR : %s%i%s\n", YLW, shell->line.cmd_nbr, NTL);
	while (i < shell->line.cmd_nbr)
	{
		if (shell->line.cmd[i].args != NULL
			&& shell->line.cmd[i].args[0] != NULL)
		{
			shell->line.cmd[i].name = ft_strdup(shell->line.cmd[i].args[0]);
			if (shell->line.cmd[i].name == NULL)
				return (ERROR);
		}
		ft_printf(1, "CMD[%i] input [%i] output [%i] : ", i,
			shell->line.cmd[i].input, shell->line.cmd[i].output); 
		for (int k = 0; shell->line.cmd[i].args[k] != NULL; k++)
			ft_printf(1, "%s[%s]%s", YLW, shell->line.cmd[i].args[k], NTL);
		ft_printf(1, "\n"); 
		// ft_printf(1, "CMD[%i] : %t\n", i, shell->line.cmd[i].args);
		i++;
	}
	return (TRUE);
}
