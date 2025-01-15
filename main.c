/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:00:46 by tgoudman          #+#    #+#             */
/*   Updated: 2025/01/15 13:40:07 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const *argv[])
{
	char	*input;

	(void)argv;
	(void)argc;
	while (1)
	{
		input = readline("Input: ");
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
