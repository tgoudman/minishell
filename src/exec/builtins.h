/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:07:05 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/10 13:17:08 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct	s_cmd t_cmd;
typedef int	(*t_builtins)(t_bash *, t_cmd *, int);

typedef struct s_func
{
	const char	*name;
	t_builtins	exec;
	int			rtn;
}	t_func;

//BUILTIN
void	init_func(t_func *builtin);
int 	ft_echo(t_bash *shell, t_cmd *cmd, int output);
int		ft_cd(t_bash *shell, t_cmd *cmd, int output);
int		ft_pwd(t_bash *shell, t_cmd *cmd, int output);
int		ft_export(t_bash *shell, t_cmd *cmd, int output);
int		ft_unset(t_bash *shell, t_cmd *cmd, int output);
int		ft_env(t_bash *shell, t_cmd *cmd, int output);
int		ft_exit(t_bash *shell, t_cmd *cmd, int output);
int		ft_execve(t_bash *shell, t_cmd *cmd);
void	ft_heredoc(char *str, char	*del);
void	find_inpout_output(t_bash *shell);
int		ft_test(t_bash *shell, int inpout, int outpout);
void	find_inpout_output(t_bash *shell);
int		ft_append(char *str);
int		ft_open_file(char *str, int file);
void	close_fd(t_bash *shell);

//TEST
t_cmd	*init_test(void);
void	init_file(t_bash *shell);

#endif