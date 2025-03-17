/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_remake_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:35:03 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/10 14:55:48 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	return (FALSE);
}

void	replace_and_convert_tab(char **tmp, char *input, int *i, int *j)
{
	if (input[(*i)] == '\t')
		(*tmp)[(*j)++] = ' ';
	else
		(*tmp)[(*j)++] = input[(*i)++];
}
