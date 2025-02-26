/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:13:20 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/26 10:47:31 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_struct(t_bash *shell, char **env)
{
	shell->prev_return = 0;
	init_env(shell, env);
	init_signale();
	init_func(shell->func);
	return (0);
}
