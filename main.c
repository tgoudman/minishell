/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:00:46 by tgoudman          #+#    #+#             */
/*   Updated: 2025/01/22 12:20:54 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char const **argv, char **env)
{
	t_bash	            shell;
	
	(void)argv;
	(void)argc;
	ft_minishell(&shell, env);
	return (0);
}
