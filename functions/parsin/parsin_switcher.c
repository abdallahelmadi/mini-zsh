/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_switcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:00:53 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/25 20:32:58 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_switcher(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	t_cmd_line	*tty;

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
				{
					tty = tempnode->next->next->next;
					tempnode->next->next->next = tempnode;
					*cmd_list = tempnode->next->next;
					tempnode->prev = tempnode->next->next;
					tempnode->next->next = tty;
					if (tty)
						tty->prev = tempnode->next;
				}
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
			/*::::::::::::::::::::::::::::::::::::::::::: SOVE :::::::::::::::::::::::::::::::::::::::*/
			// if (tempnode->prev == NULL)
			// {
			// 	ttynode = utils_new_node("test");
			// 	ttynode->type = TP_CMD;
			// 	*cmd_list = ttynode;
			// 	ttynode->next = tempnode;
			// 	tempnode->prev = ttynode;
			// }
			// else
			// {
			// 	ttynode = utils_new_node("test");

			// 	if (tempnode->prev && tempnode->prev->type != TP_PIPE)
			// 		ttynode->type = TP_STRING;
			// 	else
			// 		ttynode->type = TP_CMD;

			// 	// Link ttynode before tempnode
			// 	ttynode->next = tempnode;
			// 	ttynode->prev = tempnode->prev;

			// 	if (tempnode->prev)
			// 		tempnode->prev->next = ttynode;

			// 	tempnode->prev = ttynode;
			// }
		}
		tempnode = tempnode->next;
	}
}
