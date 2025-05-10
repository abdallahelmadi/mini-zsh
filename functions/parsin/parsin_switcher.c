/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_switcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:00:53 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/10 12:19:30 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	function_sl_norm_n1(t_cmd_line **cmd_list, t_cmd_line **tempnode)
{
	t_cmd_line	*tty;

	tty = (*tempnode)->next->next->next;
	(*tempnode)->next->next->prev = NULL;
	(*tempnode)->next->next->next = (*tempnode);
	*cmd_list = (*tempnode)->next->next;
	(*tempnode)->prev = (*tempnode)->next->next;
	(*tempnode)->next->next = tty;
	if (tty)
		tty->prev = (*tempnode)->next;
}

void	parsin_switcher(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;

	tempnode = *cmd_list;
	while (tempnode)
	{
		if (tempnode->type == TP_REDIR1 || tempnode->type == TP_REDIR11
			|| tempnode->type == TP_REDIR2 || tempnode->type == TP_REDIR22)
		{
			while (tempnode->next->next
					&& tempnode->next->next->type != TP_PIPE
					&& tempnode->next->next->type != TP_REDIR1
					&& tempnode->next->next->type != TP_REDIR11
					&& tempnode->next->next->type != TP_REDIR2
					&& tempnode->next->next->type != TP_REDIR22
				)
			{
				if (tempnode->prev == NULL)
					function_sl_norm_n1(cmd_list, &tempnode);
				else
				{
					tempnode->prev->next = tempnode->next->next;
					tempnode->next->next->prev = tempnode->prev;
					tty = tempnode->next->next->next;
					tempnode->next->next->next = tempnode;
					tempnode->prev = tempnode->next->next;
					tempnode->next->next = tty;
					if (tty)
						tty->prev = tempnode->next;
				}
			}
		}
		tempnode = tempnode->next;
	}
	tempnode = *cmd_list;
	t_cmd_line	*ttynode;
	while (tempnode)
	{
		if (tempnode->type == TP_REDIR1 || tempnode->type == TP_REDIR11 || tempnode->type == TP_REDIR2 || tempnode->type == TP_REDIR22)
		{
			if (tempnode->prev == NULL)
			{
				ttynode = utils_new_node("true");
				ttynode->type = TP_CMD;
				*cmd_list = ttynode;
				ttynode->next = tempnode;
				tempnode->prev = ttynode;
			}
			else if (tempnode->prev == NULL || tempnode->prev->type == TP_PIPE)
			{
				ttynode = utils_new_node("true");
				if (tempnode->prev && tempnode->prev->type != TP_PIPE)
					ttynode->type = TP_STRING;
				else
					ttynode->type = TP_CMD;
				ttynode->next = tempnode;
				ttynode->prev = tempnode->prev;
				if (tempnode->prev)
					tempnode->prev->next = ttynode;
				tempnode->prev = ttynode;
			}
		}
		tempnode = tempnode->next;
	}
}
