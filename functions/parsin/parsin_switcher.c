/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_switcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:00:53 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/14 09:27:59 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cci_1(t_cmd_line **tempnode, t_cmd_line **cmd_list)
{
	t_cmd_line	*tty;

	tty = NULL;
	tty = (*tempnode)->next->next->next;
	(*tempnode)->next->next->prev = NULL;
	(*tempnode)->next->next->next = *tempnode;
	*cmd_list = (*tempnode)->next->next;
	(*tempnode)->prev = (*tempnode)->next->next;
	(*tempnode)->next->next = tty;
	if (tty)
		(tty)->prev = (*tempnode)->next;
}

static void	cci_2(t_cmd_line **tempnode)
{
	t_cmd_line	*tty;

	tty = NULL;
	(*tempnode)->prev->next = (*tempnode)->next->next;
	(*tempnode)->next->next->prev = (*tempnode)->prev;
	tty = (*tempnode)->next->next->next;
	(*tempnode)->next->next->next = *tempnode;
	(*tempnode)->prev = (*tempnode)->next->next;
	(*tempnode)->next->next = tty;
	if (tty)
		(tty)->prev = (*tempnode)->next;
}

void	parsin_switcher(t_cmd_line **cmd_list)
{
	t_cmd_line	*t;
	t_cmd_line	*n;

	t = *cmd_list;
	while (t)
	{
		if ((t->type == TP_REDIR1 || t->type == TP_REDIR11
				|| t->type == TP_REDIR2 || t->type == TP_REDIR22)
			&& t->next && t->next->next)
		{
			n = t->next->next;
			while (n && n->type != TP_PIPE && n->type != TP_REDIR1
				&& n->type != TP_REDIR11 && n->type != TP_REDIR2
				&& n->type != TP_REDIR22)
			{
				n = n->next;
				if (t->prev == NULL)
					cci_1(&t, cmd_list);
				else
					cci_2(&t);
			}
		}
		t = t->next;
	}
}
