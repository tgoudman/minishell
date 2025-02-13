/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_remake2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:09:19 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/12 14:37:07 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*input_remake2(t_lst_var *lst_var)
{
	t_lst_var	*tmp;
	char		*input;
	char		*temp;
	int			id;

	id = 0;
	input = ft_strdup("");
	tmp = lst_var;
	while (tmp != NULL)
	{
		if (id > 0)
		{
			temp = input;
			input = ft_strjoin(temp, " ");
			free(temp);
		}
		if (tmp->is_squote != FALSE)
		{
			temp = input;
			if (tmp->is_squote == 34)
				input = ft_strjoin(temp, "\"");
			if (tmp->is_squote == 39)
				input = ft_strjoin(temp, "'");
			free(temp);
		}
		temp = input;
		input = ft_strjoin(temp, ft_strdup(tmp->string));
		free(temp);
		if (tmp->is_squote != FALSE)
		{
			temp = input;
			if (tmp->is_squote == 34)
				input = ft_strjoin(temp, "\"");
			if (tmp->is_squote == 39)
				input = ft_strjoin(temp, "'");
			free(temp);
		}
		tmp = tmp->next;
		id++;
	}
	input = input_remake(input);
	return (input);
}
