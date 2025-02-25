/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:52:24 by jdhallen          #+#    #+#             */
/*   Updated: 2025/02/14 11:35:31 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_signal(int sig, int access)
{
	static int	return_value;
	int			temp;

	if (access == 1)
		return_value = sig;
	if (access == 0)
	{
		temp = return_value;
		return_value = 0;
		return (temp);
	}
	return (130);
}

void	handler(int signum)
{
	if (signum == SIGINT)
		return_signal(130, 1);
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signale(struct sigaction *sa)
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
}
