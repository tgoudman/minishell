/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_remake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:23:04 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/10 14:59:59 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *input, int i)
{
	while (input[i] != '\0' && if_whitespace(input[i]))
		i++;
	if (input[i] == '\0')
		return (FALSE);
	return (TRUE);
}

void	move_in_input(char *input, int i, char *quote)
{
	if (*quote != FALSE && input[i] == *quote)
		*quote = FALSE;
	else if (*quote == FALSE && (input[i] == 34 || input[i] == 39))
		*quote = input[i];
}

char	*copy_space(char *input, char *tmp)
{
	char	quote;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	space = 1;
	quote = FALSE;
	while (input[i] != '\0' && check_space(input, i) == TRUE)
	{
		move_in_input(input, i, &quote);
		if (if_whitespace(input[i]) && space == 1 && quote == FALSE)
			i++;
		else
		{
			if (if_whitespace(input[i]) && quote == FALSE)
				space = 1;
			else
				space = 0;
			replace_and_convert_tab(&tmp, input, &i, &j);
		}
	}
	return (tmp[j] = '\0', tmp);
}

int	move_space(char *input)
{
	char	quote;
	int		space;
	int		i;
	int		len;

	i = 0;
	len = 0;
	quote = FALSE;
	space = 1;
	while (input[i] != '\0' && check_space(input, i) == TRUE)
	{
		move_in_input(input, i, &quote);
		if (if_whitespace(input[i]) && space == 1 && quote == FALSE)
			i++;
		else
		{
			if (if_whitespace(input[i]) && quote == FALSE)
				space = 1;
			else
				space = 0;
			i++;
			len++;
		}
	}
	return (len);
}

char	*input_remake(char *input)
{
	char	*tmp;
	char	*res;

	tmp = malloc((move_space(input) + 1) * sizeof (char));
	if (tmp == NULL)
		return (NULL);
	res = copy_space(input, tmp);
	free(input);
	return (res);
}
