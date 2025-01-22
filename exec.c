/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:29:28 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/22 16:29:07 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_function(t_bash *shell)
{
	if (ft_strncmp(shell->line.cmd.args[0], "echo", 5) == 0)
		shell->func[ECHO].exec(shell, 1);
	if (ft_strncmp(shell->line.cmd.args[0], "cd", 3) == 0)
		shell->func[CD].exec(shell, 1);
	if (ft_strncmp(shell->line.cmd.args[0], "pwd", 4) == 0)
		shell->func[PWD].exec(shell, 1);
	if (ft_strncmp(shell->line.cmd.args[0], "export", 7) == 0)
		shell->func[EXPORT].exec(shell, 1);
	if (ft_strncmp(shell->line.cmd.args[0], "env", 4) == 0)
		shell->func[ENV].exec(shell, 1);
	return (0);
}
