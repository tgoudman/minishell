/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:07:05 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/25 11:28:09 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_line	t_line;
typedef struct s_func	t_func;
typedef struct s_bash	t_bash;
typedef struct s_cmd	t_cmd;

//BUILTIN
int		ft_echo(t_bash *shell, t_cmd *cmd, int output);
int		ft_cd(t_bash *shell, t_cmd *cmd, int output);
int		ft_pwd(t_bash *shell, t_cmd *cmd, int output);
int		ft_export(t_bash *shell, t_cmd *cmd, int output);
int		ft_unset(t_bash *shell, t_cmd *cmd, int output);
int		ft_env(t_bash *shell, t_cmd *cmd, int output);
int		ft_exit(t_bash *shell, t_cmd *cmd, int output);
int		ft_execve(t_bash *shell);
int		init_execve(t_bash *shell);
int		ft_append(char *str);
int		ft_open_file(char *str, int file);
void	close_fd(t_bash *shell);
void	init_func(t_func *builtin);
char	*search_file(t_bash *shell, int index_cmd);
void	redirect_fd(t_bash *shell, char *str);
int		get_fd(t_bash *shell, char *str);
int		check_cmds(t_bash *shell);
void	redirect_fd_infile(t_bash *shell, char *str);
char	*search_infile(t_bash *shell);
int		check_function(t_cmd cmd);
int		open_fds(t_bash *shell);
int		check_cmds(t_bash *shell);
void	launch_builtins(t_bash *shell, int index, int pipe_fd);
void	launch_cmd(t_bash *shell, t_cmd cmd, int index);
char	*get_path(t_bash *shell, char *cmd);
int		ft_atoi_exit(const char *nptr);

//HEREDOCS
void	init_heredocs(t_bash *shell);
int		ft_heredoc(char *del, char *str);
char	*handle_multiple_heredocs(t_bash *shell);
void	do_pipe(t_bash *shell, t_cmd cmd, int index);
void	ft_execve_heredocs(t_bash *shell, char *str);
int		get_cmd(t_bash	*shell, char *str);
void	close_fd_heredocs(t_bash *shell);

#endif