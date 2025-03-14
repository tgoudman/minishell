/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:30:22 by jdhallen          #+#    #+#             */
/*   Updated: 2025/03/14 10:04:58 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_stop = 0;

int	interactive_mode(int boolean)
{
	static int	result;

	if (boolean != ERROR)
		result = boolean;
	if (result == TRUE)
		return (TRUE);
	return (FALSE);
}

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

int	interactive_mode_heredocs(int boolean)
{
	static int	result;

	if (boolean != ERROR)
		result = boolean;
	if (result == TRUE)
		return (TRUE);
	return (FALSE);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (interactive_mode_heredocs(ERROR) == TRUE)
	{
		if (signum == SIGINT)
		{
			g_stop = 1;
			ft_printf(1, "\n");
		}
	}
	else if (interactive_mode(ERROR) == TRUE)
	{
		if (signum == SIGINT)
		{
			return_signal(130, 1);
			ft_printf(1, "\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else
		ft_printf(1, "\n");
}

void	init_signale(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_sigaction = handler;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		perror("Signal error");
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = 0;
	sigemptyset(&sigquit.sa_mask);
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		perror("Signal error");
}
