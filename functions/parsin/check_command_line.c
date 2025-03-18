/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/18 21:04:25 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	*new_node(const char *data)
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

static t_cmd_line	*last_node(t_cmd_line *header)
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

// static t_cmd_line	*delete_node(t_cmd_line **node)
// {
// 	t_cmd_line	*before;
// 	t_cmd_line	*after;

// 	before = (*node)->prev;
// 	after = (*node)->next;
// 	after->prev = before;
// 	if (before != NULL)
// 		before->next = after;
// 	*node = after;
// 	return (after);
// }

static t_cmd_line	*replace_node(t_cmd_line **org, t_cmd_line **node, t_cmd_line **new_list)
{
	t_cmd_line	*temp;

	temp = (*node)->prev;
	if (temp != NULL)
		temp->next = (*new_list);
	(*new_list)->prev = temp;
	last_node(*new_list)->next = (*node)->next;
	if ((*node)->next != NULL)
		((*node)->next)->prev = last_node(*new_list);
	if (temp == NULL)
		return (*new_list);
	return (*org);
}








































static t_cmd_line	*split_command_as_list(const char *command_line)
{
	t_cmd_line	*globalnode;
	t_cmd_line	*tempnodevx;
	t_cmd_line	*tempnodepr;
	t_cmd_line	*tempnodenw;
	t_cmd_line	*tempnode;
	char		**tempv0;
	char		*zmax;
	int			index;

	globalnode = NULL;
	index = 0;
	tempv0 = NULL;
	zmax = utils_strjoin(" ", command_line, " ");
	if (utils_strstr(zmax, "|"))
	{
		tempv0 = utils_split(zmax, '|');
		if (tempv0 == NULL)
			return (NULL);
		globalnode = new_node(tempv0[0]);
		index++;
		while (tempv0[index] != NULL)
		{
			tempnodepr = last_node(globalnode);
			tempnodenw = new_node("|");
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			tempnodepr = last_node(globalnode);
			tempnodenw = new_node(tempv0[index]);
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			index++;
		}
	}

	index = 0;
	if (tempv0 == NULL && utils_strstr(zmax, "<<"))
	{
		tempv0 = utils_split_pro(zmax, "<<");
		if (tempv0 == NULL)
			return (NULL);
		globalnode = new_node(tempv0[0]);
		index++;
		while (tempv0[index] != NULL)
		{
			tempnodepr = last_node(globalnode);
			tempnodenw = new_node("<<");
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			tempnodepr = last_node(globalnode);
			tempnodenw = new_node(tempv0[index]);
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			index++;
		}
	}
	else if (tempv0 != NULL && utils_strstr(zmax, "<<"))
	{
		tempnodevx = globalnode;
		while (tempnodevx != NULL)
		{
			index = 0;
			if (utils_strstr(tempnodevx->data, "<<"))
			{
				tempv0 = utils_split_pro(utils_strjoin(" ", tempnodevx->data, " "), "<<");
				if (tempv0 == NULL)
					return (NULL);
				tempnode = new_node(tempv0[0]);
				index++;
				while (tempv0[index] != NULL)
				{
					tempnodepr = last_node(tempnode);
					tempnodenw = new_node("<<");
					tempnodepr->next = tempnodenw;
					tempnodenw->prev = tempnodepr;
					tempnodepr = last_node(tempnode);
					tempnodenw = new_node(tempv0[index]);
					tempnodepr->next = tempnodenw;
					tempnodenw->prev = tempnodepr;
					index++;
				}
				globalnode = replace_node(&globalnode, &tempnodevx, &tempnode);
			}
			tempnodevx = tempnodevx->next;
		}
	}
	
	return (globalnode);
}











void	check_command_line(const char *command_line)
{
	t_cmd_line	*cmd_list;

	if (command_line[0] == '\0')
		free ((char *)command_line);
	else if (!utils_strcmp(command_line, '&') || utils_strstr(command_line, ">>>")
		|| !utils_strcmp(command_line, '(') || !utils_strcmp(command_line, ')')
		|| !utils_strcmp(command_line, '*') || !utils_strcmp(command_line, ';')
		|| utils_strstr(command_line, "<<<") || !utils_strcmp(command_line, '#')
		|| !utils_strcmp(command_line, '\\')
		|| utils_strstr(command_line, "||"))
	{
		free ((char *)command_line);
		printf("minishell: something unsupported\n");
		g_lastexitstatus = FAILURE;
	}
	else
	{
		cmd_list = split_command_as_list(command_line);
		free ((char *)command_line);
		while (cmd_list != NULL)
		{
			printf("[%s]", cmd_list->data);
			cmd_list = cmd_list->next;
			if (cmd_list != NULL)
				printf(" -> ");
		}
		printf("\n");
		g_lastexitstatus = SUCCESS;
	}
}
