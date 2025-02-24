/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:13:20 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/14 11:46:06 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_struct(t_bash *shell, char **env)
{
	struct sigaction	sa;

	shell->prev_return = 0;
	init_env(shell, env);
	init_signale(&sa);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Signal error");
	init_func(shell->func);
	return (0);
}
