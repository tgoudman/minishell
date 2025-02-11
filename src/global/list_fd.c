/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:23:16 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/07 12:42:29 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_fd    *create_new_node_fd(char *name, char type, char *limit)
{
    t_lst_fd    *new_node;
    new_node = malloc(sizeof(t_lst_fd));
    if (!new_node)
        return (NULL);
    new_node->name = name;
    new_node->type = type;
    new_node->limit = limit;
    new_node->next = NULL;
    return (new_node);
}
void    list_add_back_fd(t_lst_fd **list, t_lst_fd *new_node)
{
    t_lst_fd *tmp;

    tmp = *list;
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->next = NULL;
}
void    ft_printf_list_fd(t_lst_fd **list, int output)
{
    t_lst_fd    *tmp;
    int         i;

    tmp = *list;
    i = 0;
    while (tmp)
    {
        // Affichage des informations de base
        ft_printf(output, "FD %i is \033[34m%s\033[0m of type %c so", i, tmp->name ? tmp->name : "Unknown", tmp->type);

        // Affichage du type spécifique
        if (tmp->type == 'i')
            ft_printf(output, " type \033[34minput\033[0m\n");
        else if (tmp->type == 'o')
            ft_printf(output, " type \033[34moutput\033[0m\n");
        else if (tmp->type == 'a')
            ft_printf(output, " type \033[34mappend\033[0m\n");
        else if (tmp->type == 'h')
            ft_printf(output, " type \033[34mheredoc\033[0m with limiter \033[34m%s\033[0m\n", tmp->limit ? tmp->limit : "No limit");
        else
            ft_printf(output, " type \033[34munknown\033[0m\n");
        i++;
        tmp = tmp->next;
    }
	printf("taille de la liste FD == %d\n\n", i);
}