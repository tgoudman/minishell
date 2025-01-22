/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhallen <jdhallen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:54:13 by jdhallen          #+#    #+#             */
/*   Updated: 2025/01/22 16:29:04 by jdhallen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef ERROR
#  define ERROR -1
# endif

typedef enum e_command
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    CMD_COUNT
} t_command;

typedef struct s_var
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_var;

typedef struct s_cmd
{
	char *cmd_name;
	char **args;
}	t_cmd;

typedef struct s_line
{
	t_cmd	cmd;
	char 	*input_file;
	char 	*output_file;
	int 	input_fd;
	int 	output_fd;
	int		append;
	int		hd;
	int		id;
}	t_line;

typedef struct s_lst
{
	struct s_lst	*next;
	char				*name; 
	char				*data;
}		t_lst;

typedef struct s_bash t_bash;

typedef void	(*t_builtins)(t_bash *, int);

typedef struct s_func
{
	const char	*name;
	t_builtins	exec;
	int			rtn;
}	t_func;

typedef struct s_bash
{
	t_line	line;
	int		prev_return;
	t_func		func[7];
	struct s_lst	*lst_env;
}	t_bash;

//EXEC
int	single_function(t_bash *shell);

//INIT FUNCTION
void	init_env(t_bash *shell, char const **env);
int 	init_struct(t_bash *shell, char const **env);

// MAIN FUNCTION
void	ft_minishell(t_bash *shell, char const **env);

// SIGNALE
void	init_signale(struct sigaction *sa);
void 	handler(int signum);
int 	return_signal(int sig, int access);

//PARSING
int	cmd_manager(t_bash *shell, char *input);
int parsing(t_bash *shell);

//CLEANING

void	free_cmd(char **cmd);
void	free_list(t_lst **shell);

//LST
t_lst	*create_new_node(char *data, char *name);
void	list_add_back(t_lst **list, t_lst *new_node);
void	ft_printf_list(t_lst **list, int output);
char	*get_name(char *str);
char	*get_data(char *str);


//BUILTIN

void	init_func(t_func *builtin);
int 	ft_echo(t_bash *shell, int output);
int		ft_cd(t_bash *shell, int output);
int		ft_pwd(t_bash *shell, int output);
int		ft_export(t_bash *shell, int output);
int		ft_unset(t_bash *shell, int output);
int		ft_env(t_bash *shell, int output);
int		ft_exit(t_bash *shell, int output);


#endif