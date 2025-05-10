/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:00:12 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/08 22:00:12 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		else if (temp->type == TP_REDIR22 && temp->next)
			temp = temp->next->next;
		else
			temp = temp->next;
	}
	return (0);
}
