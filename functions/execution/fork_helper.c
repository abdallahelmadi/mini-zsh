/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:57:28 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/10 18:07:08 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_builtin_process(t_cmd_line *node)
{
	handle_redirections(node);
	if (g_global.g_signal == 1)
		return ;
	execution_with_builtin(node);
}

void	execution_with_builtin(t_cmd_line *node)
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

void	heredoc_open(t_cmd_line *node)
{
	t_cmd_line	*temp;
	int			fd_heredoc;

	temp = node;
	while (temp && temp->type != TP_PIPE)
	{
		if (temp->type == TP_REDIR22 && temp->next)
		{
			fd_heredoc = open(temp->next->data, O_RDONLY);
			if (fd_heredoc == -1)
			{
				printf("minishell: %s: No such file or directory\n",
					node->next->data);
				exit(FAILURE);
			}
			dup2(fd_heredoc, 0);
			close(fd_heredoc);
			break ;
		}
		temp = temp->next;
	}
}
