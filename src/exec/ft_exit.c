/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nezumickey <nezumickey@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:39:23 by tgoudman          #+#    #+#             */
/*   Updated: 2025/03/16 04:03:18 by nezumickey       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi_exit(const char *nptr)
{
	int			i;
	int			s;
	long		n;

	i = 0;
	s = 1;
	n = 0;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0' || n > INT_MAX || n * s < INT_MIN)
		return (printf("%s: numeric argument required\n", nptr), 2);
	return (n * s);
}

int	ft_exit(t_bash *shell, t_cmd *cmd, int output)
{
	int	i;

	i = 0;
	(void)output;
	while (cmd->args[i])
		++i;
	if (i > 2)
	{
		shell->prev_return = 1;
		printf("bash: exit: too many arguments\n");
	}
	if (i == 2)
		shell->prev_return = ft_atoi_exit(cmd->args[1]);
	free_list_env(shell->lst_env);
	if (cmd->args)
		free_cmd(cmd->args);
	if (cmd->name)
		free(cmd->name);
	if (shell->line.cmd)
		free(shell->line.cmd);
	if (shell->line.group)
		free_cmd(shell->line.group);
	exit(shell->prev_return);
	return (0);
}
