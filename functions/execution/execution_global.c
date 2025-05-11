/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/10 18:41:10 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	prepare_all_heredoc(t_cmd_line *node)
{
	t_cmd_line	*tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp->type == TP_REDIR22 && tmp->next)
		{
			read_to_delimeter(tmp);
		}
		tmp = tmp->next;
	}
}

static void	handle_exit_status(pid_t last_pid)
{
	int		status;
	int		sig;

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
}

void	execution_global(t_cmd_line **cmd_list)
{
	pid_t	last_pid;
	pid_t	pid;

	prepare_all_heredoc(*cmd_list);
	if (g_global.g_signal == 1)
	{
		g_global.g_signal = 0;
		utils_setexit(SIGNAL_SIGINT);
		restore();
		return ;
	}
	last_pid = execution_part(cmd_list);
	handle_exit_status(last_pid);
	pid = wait(NULL);
	while (pid > 0)
	{
		pid = wait(NULL);
	}
	g_global.g_foreground_running = 0;
	restore();
}
