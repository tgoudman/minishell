/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:52:24 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/22 12:02:08 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int return_signal(int sig, int access)
{
	static int return_value;

	if (access == 1)
		return_value = sig;
	if (access == 0)
		return (return_value);
	return (130);
}

void handler(int signum)
{
	int	res;

	if (signum == SIGINT)
		res = return_signal(130, 1);
	ft_printf(1, "\nInput: ");
	fflush(stdout);
}

void	init_signale(struct sigaction *sa)
{
	// Définir le gestionnaire pour SIGINT
	sa->sa_handler = handler;  // Spécifier la fonction à appeler lors de SIGINT
	sa->sa_flags = 0;		// Pas d'options spéciales
	sigemptyset(&sa->sa_mask);	 // Aucun signal à bloquer pendant le traitement du signal
}
