/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_switcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:00:53 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/11 11:49:28 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	cci_1(t_cmd_line **tempnode, t_cmd_line **tty,
	t_cmd_line **cmd_list)
{
	(*tty) = (*tempnode)->next->next->next;
	(*tempnode)->next->next->prev = NULL;
	(*tempnode)->next->next->next = (*tempnode);
	*cmd_list = (*tempnode)->next->next;
	(*tempnode)->prev = (*tempnode)->next->next;
	(*tempnode)->next->next = (*tty);
	if ((*tty))
		(*tty)->prev = (*tempnode)->next;
}

static void	cci_2(t_cmd_line **tempnode, t_cmd_line **tty)
{
	(*tempnode)->prev->next = (*tempnode)->next->next;
	(*tempnode)->next->next->prev = (*tempnode)->prev;
	(*tty) = (*tempnode)->next->next->next;
	(*tempnode)->next->next->next = (*tempnode);
	(*tempnode)->prev = (*tempnode)->next->next;
	(*tempnode)->next->next = (*tty);
	if ((*tty))
		(*tty)->prev = (*tempnode)->next;
}

void	parsin_switcher(t_cmd_line **cmd_list)
{
	t_cmd_line	*t;
	t_cmd_line	*tty;
	t_cmd_line	*n;

	t = *cmd_list;
	tty = NULL;
	while (t)
	{
		if (t->type == TP_REDIR1 || t->type == TP_REDIR11
			|| t->type == TP_REDIR2 || t->type == TP_REDIR22)
		{
			n = t->next->next;
			while (n && n->type != TP_PIPE && n->type != TP_REDIR1
				&& n->type != TP_REDIR11 && n->type != TP_REDIR2
				&& n->type != TP_REDIR22
			)
			{
				if (t->prev == NULL)
					cci_1(&t, &tty, cmd_list);
				else
					cci_2(&t, &tty);
			}
		}
		t = t->next;
	}
}
