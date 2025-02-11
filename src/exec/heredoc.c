/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:13 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/10 10:35:04 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(char *str, char	*del)
{
	int		fd;
	char	*input;

	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror("Erreur lors de l'ouverture du fichier"));
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL)
		{
			printf("!!here-document delimited by end-of-file (wanted `%s')!!\n",
				del);
			break ;
		}
		if (ft_strcmp(input, del) == 0)
			break ;
		ft_putendl_fd(input, fd);
	}
}