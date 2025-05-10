/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:02:24 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/08 22:02:24 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execution_with_builtin(t_cmd_line *node)
{
	if (utils_strcmp(node->data, "export") == 0)
		builtin_export(node);
	else if (utils_strcmp(node->data, "unset") == 0)
		builtin_unset(node);
	else if (utils_strcmp(node->data, "env") == 0)
		builtin_env(node);
	else if (utils_strcmp(node->data, "pwd") == 0)
		builtin_pwd(node);
	else if (utils_strcmp(node->data, "exit") == 0)
		builtin_exit(node);
	else if (utils_strcmp(node->data, "echo") == 0)
		builtin_echo(node);
	else if (utils_strcmp(node->data, "cd") == 0)
		builtin_cd(node);
	else
		execution_v(node);
}
static void heredoc_open(t_cmd_line *node)
{
    t_cmd_line  *temp;
	int         fd_heredoc;
    
    temp = node;
    while (temp && temp->type != TP_PIPE)
    {
        if (temp->type == TP_REDIR22 && temp->next)
	    {
            fd_heredoc = open(temp->next->data, O_RDONLY);
	        if (fd_heredoc == -1)
	        {
	        	printf("minishell: %s: No such file or directory\n", node->next->data);
	        	exit(FAILURE);
	        }
	        dup2(fd_heredoc, 0);
	        close(fd_heredoc);
            break;
        }
        temp = temp->next;
    }
}
static void handle_builtin_process(t_cmd_line *node)
{
	handle_redirections(node);
	if (g_global.g_signal == 1)
		return;
	execution_with_builtin(node);
}
static void save_stdin_stdout(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}
static void restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
static void start_child_process(t_cmd_line *node, int *fd, int *prev_read)
{
    setup_for_child();
    if (has_heredoc(node))
        heredoc_open(node);
    if (*prev_read != 0 && !has_heredoc(node))
    {
        dup2(*prev_read, 0);
        close(*prev_read);
    }
    if (handle_redirections(node))
        exit(FAILURE);
    if (g_global.g_signal == 1)
        exit(SIGNAL_SIGINT);
    if (has_pipe(node))
        dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    execution_with_builtin(node);
    exit(SUCCESS);
}
static void fork_and_pipe(t_cmd_line *node, int *fd, int *prev_read, int *last_pid)
{
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
        start_child_process(node, fd, prev_read);
	else
	{
		close(fd[1]);
		if (*prev_read != 0)
			close(*prev_read);
		*prev_read = fd[0];
		*last_pid = pid;
	}
}
pid_t	execution_part(t_cmd_line **node)
{
	int	fd[2];
	int	prev_read = 0;
	int	saved_stdin;
	int saved_stdout;
	pid_t	last_pid;
	t_cmd_line *temp = *node;

	last_pid = -1;
	g_global.g_foreground_running = 1;
	while (temp)
	{
		save_stdin_stdout(&saved_stdin, &saved_stdout);
		if (is_builtin_for_parent(temp))
			handle_builtin_process(temp);
		else
			fork_and_pipe(temp, fd, &prev_read ,&last_pid);
		restore_stdin_stdout(saved_stdin, saved_stdout);
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	return (last_pid);
}
