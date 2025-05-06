/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 17:27:43 by bnafiai          ###   ########.fr       */
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

int	is_builtin_for_parent(t_cmd_line *node)
{
	if (utils_strstr_pro(node->data, "cd") || utils_strstr_pro(node->data, "export")
		|| utils_strstr_pro(node->data, "unset") || utils_strstr_pro(node->data, "exit"))
		return (1);
	return (0);
}

int	has_pipe(t_cmd_line *node)
{
	t_cmd_line *temp = node;
	while (temp)
	{
		if (temp->type == TP_PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}
int	has_heredoc(t_cmd_line *node)
{
	t_cmd_line *temp = node;
	while (temp)
	{
		if (temp->type == TP_REDIR22)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	handle_redirections(t_cmd_line *node)
{
	t_cmd_line *temp = node;
	while (temp)
	{
		if (temp->type == TP_REDIR1)
		{
			if (write_to(temp))
				return (1);
			temp = temp->next->next;
		}
		else if (temp->type == TP_REDIR11)
		{
			if (write_into(temp))
				return (1);
			temp = temp->next->next;
		}
		else if (temp->type == TP_REDIR2)
		{
			if (read_from(temp))
				return(1);
			temp = temp->next->next;
		}
		else if (temp->type == TP_REDIR22)
		{
			read_to_delimeter(temp);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (0);
}

pid_t	execution_part(t_cmd_line **node)
{
	int	fd[2];
	int	prev_read = 0;
	pid_t	pid;
	int	saved_stdin;
	int saved_stdout;
	pid_t	last_pid;
	t_cmd_line *temp = *node;
	t_cmd_line *temp_check;

	g_global.g_foreground_running = 1;
	while (temp)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (is_builtin_for_parent(temp))
		{
			handle_redirections(temp);
			if (g_global.g_signal == 1)
				return (FAILURE);
			execution_with_builtin(temp);
		}
		else
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				setup_for_child();
				if (prev_read != 0 )
				{
					dup2(prev_read, 0);
					close(prev_read);
				}
				if (handle_redirections(temp))
					exit(FAILURE);
				if (g_global.g_signal == 1)
					exit(SIGNAL_SIGINT);
				temp_check = temp;
				if (has_pipe(temp_check))
					dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				execution_with_builtin(temp);
				exit(SUCCESS);
			}
			else
			{
				close(fd[1]);
				if (prev_read != 0)
					close(prev_read);
				prev_read = fd[0];
				last_pid = pid;
			}
		}
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
	return (last_pid);
}

void	execution_global(t_cmd_line **cmd_list)
{
	int		status;
	pid_t	last_pid;
	pid_t	pid;
	int		sig;

	status = 0;
	last_pid = execution_part(cmd_list);
	if (waitpid(last_pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			utils_setexit(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(2, "QUIT \n", 6);
			utils_setexit(128 + sig);
		}
		else
			utils_setexit(FAILURE);
	}
	while ((pid = wait(NULL)) > 0)
		;
	g_global.g_foreground_running = 0;
	restore();
}
