/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:10:40 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:32 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd_line	*utils_new_node(const char *data)
{
	t_cmd_line	*cmd;

	cmd = smalloc(sizeof(t_cmd_line));
	if (cmd == NULL)
		return (NULL);
	cmd->data = utils_strdup(data);
	cmd->type = 0;
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

t_cmd_line	*utils_replace_node(t_cmd_line **header, t_cmd_line **node,
	t_cmd_line **new_list)
{
	if (((*header)->next == NULL) && ((*header)->prev == NULL))
		*header = *new_list;
	else if ((*node)->next == NULL)
	{
		((*node)->prev)->next = (*new_list);
		(*new_list)->prev = (*node)->prev;
	}
	else if ((*node)->prev == NULL)
	{
		((*node)->next)->prev = utils_last_node(*new_list);
		utils_last_node(*new_list)->next = (*node)->next;
		*header = *new_list;
	}
	else
	{
		((*node)->prev)->next = (*new_list);
		(*new_list)->prev = (*node)->prev;
		((*node)->next)->prev = utils_last_node(*new_list);
		utils_last_node(*new_list)->next = (*node)->next;
	}
	return (utils_last_node(*new_list));
}

t_cmd_line	*utils_delete_node(t_cmd_line **list, t_cmd_line **node)
{
	if ((*node)->prev == NULL && (*node)->next == NULL)
		*list = NULL;
	else if ((*node)->prev == NULL)
	{
		*node = (*node)->next;
		(*node)->prev = NULL;
		*list = *node;
	}
	else if ((*node)->next == NULL)
	{
		*node = (*node)->prev;
		(*node)->next = NULL;
	}
	else
	{
		((*node)->prev)->next = (*node)->next;
		((*node)->next)->prev = (*node)->prev;
	}
	return (*node);
}
