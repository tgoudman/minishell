/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoudman <tgoudman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:33:07 by tgoudman          #+#    #+#             */
/*   Updated: 2025/02/11 12:23:04 by tgoudman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char *cmd)
{
	int		j;
	char	**all_path;
	char	*join;
	char	*exec;

	all_path = ft_split(getenv("PATH"), ':');
	if (!all_path)
		exit(1);
	j = 0;
	while (all_path[j])
	{
		join = ft_strjoin(all_path[j], "/");
		exec = ft_strjoin(join, cmd);
		free(join);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_cmd(all_path);
			return (exec);
		}
		free(exec);
		j++;
	}
	free_cmd(all_path);
	return (cmd);
}

int	launch_cmd(t_bash *shell, t_cmd *cmd)
{
	char	**env;
	char	*path;

	path = get_path(cmd->name);
	env = lst_to_tab(shell->lst_env);
	if (execve(path, cmd->args, env) == -1)
	{
		ft_putendl_fd("command not found: ", 2);
		ft_putendl_fd(cmd->name, 2);
		free_cmd(cmd->args);
		free_cmd(env);
		return (1);
	}
	free_cmd(env);
	free_cmd(cmd->args);
	return (0);
}

// printf("signal PID = %d\n", WIFSIGNALED(status));
//if signal == 0 -> SUCCESS_fork
void	do_pipe(t_bash *shell, t_cmd *cmd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		ft_putendl_fd("pipe failed\n", 2);
		exit (1);
	}
	pid = fork();
	if (!pid)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		launch_cmd(shell, cmd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

int	ft_execve(t_bash *shell, t_cmd *cmd)
{
	pid_t	pid;

	(void)cmd;
	// if (ft_strcmp(cmd->args[0], "!heredoc0") == 0)
	// {
	// 	heredoc(shell, cmd);
	// 	return (0);
	// }
	// printf("nbr cmd == %d\n", shell->line.cmd_nbr);
	pid = fork();
	if (pid == -1)
	{
		printf("fork failed\n");
		return (1);
	}
	if (!pid)
		find_inpout_output(shell);
		// launch_cmd(shell, cmd);
	wait(NULL);
	return (0);
}

t_cmd	*init_test(void)
{
	t_cmd	*cmd_test;

	cmd_test = malloc(sizeof(t_cmd) * 3);
	if (!cmd_test)
	{
		printf("test failed\n");
		return (NULL);
	}
	cmd_test[0].args = malloc(sizeof(char *) * 3);
	cmd_test[1].args = malloc(sizeof(char *) * 3);
	cmd_test[2].args = malloc(sizeof(char *) * 3);
	cmd_test[0].name = "ls";
	cmd_test[0].args[0] = "ls";
	cmd_test[0].args[1] = "-l";
	cmd_test[0].args[2] = NULL;
	cmd_test[1].name = "wc";
	cmd_test[1].args[0] = "wc";
	cmd_test[1].args[1] = "-l";
	cmd_test[1].args[2] = NULL;
	cmd_test[2].name = "rev";
	cmd_test[2].args[0] = "rev";
	cmd_test[2].args[1] = NULL;
	return (cmd_test);
}

void	init_file(t_bash *shell)
{
	t_lst_fd	*new_node;

	shell->line.lst_fd = NULL;
	// Ajouter les fichiers à la liste
	new_node = create_new_node_fd(ft_strdup("infile"), 'h', "AH");
	list_add_back_fd(&shell->line.lst_fd, new_node);
	new_node = create_new_node_fd(ft_strdup("file_append"), 'a', NULL);
	list_add_back_fd(&shell->line.lst_fd, new_node);
	new_node = create_new_node_fd(ft_strdup("outfile"), 'o', NULL);
	list_add_back_fd(&shell->line.lst_fd, new_node);
}

int	ft_test(t_bash *shell, int inpout, int outpout)
{
	t_cmd	*test;
	int		i;

	i = 0;
	if (shell->line.cmd->input != 0)
		dup2(shell->line.cmd->input, STDIN_FILENO);
	test = init_test();
	while (i < 2)
	{
		printf("CMD == %s\n", test[i].args[0]);
		do_pipe(shell, &test[i]);
		++i;
	}
	wait(NULL);
	printf("CMD == %s\n", test[i].args[0]);
	if (shell->line.cmd->output != 1)
		dup2(shell->line.cmd->output, STDOUT_FILENO);
	launch_cmd(shell, &test[i]);
	return (0);
}

int	init_input_outpout(t_line *line, t_cmd *cmd)
{
	int	index_cmd;
	int	i;

	i = 0;
	index_cmd = 0;
	while (line->group[i])
	{
		if(line->group[i][0] == '!')
		{
			
			i++;
		}
		if(line->group[i][0] == '|')
		{
			
		}
		else
		{
			ft_atoi(line->group[i]);
		}
		i++;
	}
}

char	get_input_output(t_bash *shell, char *str)
{
	t_lst_fd	*lst;

	lst = shell->line.lst_fd;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (ft_strcmp(str, lst->name) == 0)
			return(lst->type);
		lst = lst->next;
	}
	return (NULL);
}