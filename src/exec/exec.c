/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:29:28 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/22 17:40:09 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_function(t_bash *shell, t_cmd *cmd, int index, int fd)
{
	char	*file;
	int		file_fd;

	file_fd = -1;
	file = search_file(shell, index);
	if (file != NULL)
		file_fd = get_fd(shell, file + 1);
	if (file_fd == -1)
		file_fd = fd;
	if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (shell->func[ECHO].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (shell->func[CD].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (shell->func[PWD].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (shell->func[EXPORT].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (shell->func[UNSET].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "env", 4) == 0)
		return (shell->func[ENV].exec(shell, cmd, file_fd), 1);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (shell->func[EXIT].exec(shell, cmd, file_fd), 1);
	return (0);
}
	// else 
	// {
	// 	ft_printf(1, "Command '%s' not found\n", cmd->name);
	// 	shell->prev_return = 127;
	// }