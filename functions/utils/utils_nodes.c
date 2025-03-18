/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:10:40 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/18 22:26:09 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd_line	*utils_new_node(const char *data)
{
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	if (cmd == NULL)
		return (NULL);
	cmd->data = utils_strdup(data);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd_line	*utils_last_node(t_cmd_line *header)
{
	t_cmd_line	*temp;
	t_cmd_line	*rurn;

	temp = header;
	while (temp != NULL)
	{
		rurn = temp;
		temp = temp->next;
	}
	return (rurn);
}

t_cmd_line	*utils_delete_node(t_cmd_line **node)
{
	t_cmd_line	*before;
	t_cmd_line	*after;

	before = (*node)->prev;
	after = (*node)->next;
	after->prev = before;
	if (before != NULL)
		before->next = after;
	*node = after;
	return (after);
}

t_cmd_line	*utils_replace_node(t_cmd_line **org, t_cmd_line **node,
		t_cmd_line **new_list)
{
	t_cmd_line	*temp;

	temp = (*node)->prev;
	if (temp != NULL)
		temp->next = (*new_list);
	(*new_list)->prev = temp;
	utils_last_node(*new_list)->next = (*node)->next;
	if ((*node)->next != NULL)
		((*node)->next)->prev = utils_last_node(*new_list);
	if (temp == NULL)
		return (*new_list);
	return (*org);
}
