/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_remake_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:35:03 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/17 11:58:56 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

void	replace_and_convert_tab(char **tmp, char *input, t_var *v, char q)
{
	if (q == FALSE)
	{
		if (input[v->i] == '\t')
			(*tmp)[v->j++] = ' ';
		else
			(*tmp)[v->j++] = input[v->i++];
	}
	else
		(*tmp)[v->j++] = input[v->i++];
}
