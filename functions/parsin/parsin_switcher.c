/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_switcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:00:53 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/21 12:28:00 by abdael-m         ###   ########.fr       */
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
				if ((tempnode->prev == NULL
					|| (tempnode->prev &&
						(tempnode->prev->type == TP_PIPE
						|| tempnode->prev->type == TP_REDIR1
						|| tempnode->prev->type == TP_REDIR11
						|| tempnode->prev->type == TP_REDIR2
						|| tempnode->prev->type == TP_REDIR22
				))))
					tempnode->next->next->type = TP_CMD;
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
}
