/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:50:54 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/28 17:23:20 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *var_find(t_bash *shell, char *var, char *after)
{
	t_lst	*node;
	char	*tmp;

	node = shell->lst_env;
	while (node != NULL)
	{
		if (ft_strcmp_var(node->name, var) == 0)
		{
			tmp = ft_strjoin(node->data, after);
			return (free(var), free(after), tmp);
		}
		node = node->next;
	}
	tmp = ft_strjoin("", after);
	return (free(var), free(after), tmp);
}

char *return_var_value(t_bash *shell, char *str)
{
	char	*var;
	char	*after;
	int		var_len;

	if (str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '\0')
		return (ft_strdup("$"));
	if (str[1] == '?')
		return (ft_itoa(shell->prev_return));
	var_len = 0;
	while (str[var_len + 1] && (ft_isalnum(str[var_len + 1]) || str[var_len + 1] == '_' ))
		var_len++;
	var = ft_substr(str, 1, var_len);
	if (!var)
		return (NULL);
	after = ft_strdup(str + var_len + 1);
	if (!after)
		return (free(var), NULL);
	return (var_find(shell, var, after));
}

char **demolish_var(t_bash *shell, char **temp)
{
	char	*var;
	int		i;

	i = 0;
	while (temp[i] != NULL)
	{
		var = return_var_value(shell, temp[i]);
		free(temp[i]);
		if (var == NULL)
			temp[i] = ft_strdup("");
		else
			temp[i] = var;
		i++;
	}
	return (temp);
}

char *rebuild_temp(char **temp)
{
	char	*result;
	char	*temp_join;
	int		i;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	i = 0;
	while (temp[i] != NULL)
	{
		temp_join = ft_strjoin(result, temp[i]);
		free(result);
		if (temp_join == NULL)
			return (NULL);
		result = temp_join;
		i++;
	}
	return (result);
}

int	search_for_var(t_bash *shell)
{
	char	**temp;
	int		i;

	i = 0;
	while (shell->line.group[i] != NULL)
	{
		temp = ft_sep(shell->line.group[i], '$');
		if (temp == NULL)
			return (free_cmd(shell->line.group), ERROR);
		temp = demolish_var(shell, temp);
		if (temp == NULL)
			return (free_cmd(shell->line.group), ERROR);
		free(shell->line.group[i]);
		shell->line.group[i] = rebuild_temp(temp);
		if (shell->line.group[i] == NULL)
			return (free_cmd(shell->line.group), ERROR);
		free_cmd(temp);
		i++;
	}
	return (0);
}
