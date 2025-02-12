/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:14:58 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/12 13:50:44 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_var	*convert_lst(t_lst_var **lst_point)
{
	t_lst_var	*result;
	t_lst_var	*node;
	t_lst_var	*temp;
	int	i;
	int	id;

	i = 0;
	id = 0;
	result = NULL;
	while (lst_point[i] != NULL)
	{
		temp = lst_point[i];
		while (temp != NULL)
		{
			node = create_new_node_var(ft_strdup(temp->string), temp->is_squote);
			node->id = id;
			id++;
			list_add_back_var(&result, node);
			if (temp->next == NULL || ft_strcmp(temp->next->string, "") == 0)
				node->is_space = TRUE;
			else
				node->is_space = FALSE;
			temp = temp->next;
		}
		i++;
	}
	// ft_printf_list_var(&result, 1);
	return (result);
}
