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

static void	save_stdin_stdout(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

static void	restore_stdin_stdout(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	start_child_process(t_cmd_line *node, int *fd, int *prev_read)
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

static void	fork_and_pipe(t_cmd_line *node, int *fd,
	int *prev_read, int *last_pid)
{
	pid_t	pid;

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
	int			fd[2];
	int			prev_read;
	int			saved_std[2];
	pid_t		last_pid;
	t_cmd_line	*temp;

	temp = *node;
	prev_read = 0;
	last_pid = -1;
	g_global.g_foreground_running = 1;
	while (temp)
	{
		save_stdin_stdout(&saved_std[0], &saved_std[1]);
		if (is_builtin_for_parent(temp))
			handle_builtin_process(temp);
		else
			fork_and_pipe(temp, fd, &prev_read, &last_pid);
		restore_stdin_stdout(saved_std[0], saved_std[1]);
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	return (last_pid);
}
