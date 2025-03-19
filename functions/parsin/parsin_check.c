/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/18 22:30:47 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		globalnode = utils_new_node(tempv0[0]);
		index++;
		while (tempv0[index] != NULL)
		{
			tempnodepr = utils_last_node(globalnode);
			tempnodenw = utils_new_node("|");
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			tempnodepr = utils_last_node(globalnode);
			tempnodenw = utils_new_node(tempv0[index]);
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
		globalnode = utils_new_node(tempv0[0]);
		index++;
		while (tempv0[index] != NULL)
		{
			tempnodepr = utils_last_node(globalnode);
			tempnodenw = utils_new_node("<<");
			tempnodepr->next = tempnodenw;
			tempnodenw->prev = tempnodepr;
			tempnodepr = utils_last_node(globalnode);
			tempnodenw = utils_new_node(tempv0[index]);
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
				tempnode = utils_new_node(tempv0[0]);
				index++;
				while (tempv0[index] != NULL)
				{
					tempnodepr = utils_last_node(tempnode);
					tempnodenw = utils_new_node("<<");
					tempnodepr->next = tempnodenw;
					tempnodenw->prev = tempnodepr;
					tempnodepr = utils_last_node(tempnode);
					tempnodenw = utils_new_node(tempv0[index]);
					tempnodepr->next = tempnodenw;
					tempnodenw->prev = tempnodepr;
					index++;
				}
				globalnode = utils_replace_node(&globalnode, &tempnodevx, &tempnode);
				// utils_delete_node
			}
			tempnodevx = tempnodevx->next;
		}
	}
	
	return (globalnode);
}

void	parsin_check(const char *command_line)
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
