/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:50:13 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/31 14:36:28 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	*fill_list(char **string, const char *spliter)
{
	int			index;
	t_cmd_line	*list;
	t_cmd_line	*lastnode;
	t_cmd_line	*newnode;

	list = utils_new_node(string[0]);
	index = 1;
	while (string[index] != NULL)
	{
		if (spliter[0] != '\0')
		{
			lastnode = utils_last_node(list);
			newnode = utils_new_node(spliter);
			lastnode->next = newnode;
			newnode->prev = lastnode;
		}
		lastnode = utils_last_node(list);
		newnode = utils_new_node(string[index]);
		lastnode->next = newnode;
		newnode->prev = lastnode;
		index++;
	}
	utils_free(string);
	return (list);
}

static void	split_command_part(t_cmd_line **cmd_list, const char *spliter)
{
	t_cmd_line	*tempnode;
	t_cmd_line	*tempnextnode;
	t_cmd_line	*tempnewlist;
	char		*tempchar;
	char		**tempdoublechar;

	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		if ((utils_strlen(spliter) == 1 && utils_strstr(tempnode->data, spliter)
				&& utils_strstr(tempnode->data, spliter)[1] != spliter[0]) || (
				utils_strlen(spliter) > 1
				&& utils_strstr(tempnode->data, spliter)))
		{
			tempchar = utils_strjoin(" ", tempnode->data, " ");
			tempdoublechar = utils_split_pro(tempchar, (char *)spliter);
			free(tempchar);
			tempnewlist = fill_list(tempdoublechar, spliter);
			tempnextnode = tempnode->next;
			utils_replace_node(cmd_list, &tempnode, &tempnewlist);
			tempnode = tempnextnode;
		}
		else
			tempnode = tempnode->next;
	}
}

static void	split_command(const char *command_line, t_cmd_line **cmd_list,
		const char *spliter)
{
	char		*tempchar;
	char		**tempdoublechar;

	if ((*cmd_list) == NULL)
	{
		if (utils_strstr(command_line, spliter))
		{
			tempchar = utils_strjoin(" ", command_line, " ");
			tempdoublechar = utils_split_pro(tempchar, (char *)spliter);
			free(tempchar);
			*cmd_list = fill_list(tempdoublechar, spliter);
		}
	}
	else
		split_command_part(cmd_list, spliter);
}

static void	split_nodes_by_space(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	t_cmd_line	*tempnodenext;
	t_cmd_line	*newlist;

	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		if (utils_strstr(tempnode->data, " "))
		{
			tempnodenext = tempnode->next;
			newlist = fill_list(utils_split(tempnode->data, ' '), "\0");
			utils_replace_node(cmd_list, &tempnode, &newlist);
			tempnode = tempnodenext;
		}
		else
			tempnode = tempnode->next;
	}
}

void	parsin_make_list(const char *command_line, t_cmd_line **cmd_list)
{
	split_command(command_line, cmd_list, "|");
	split_command(command_line, cmd_list, ">>");
	split_command(command_line, cmd_list, "<<");
	split_command(command_line, cmd_list, ">");
	split_command(command_line, cmd_list, "<");
	pasrin_clean_list(cmd_list);
	if (*cmd_list == NULL)
		*cmd_list = fill_list(utils_split(command_line, ' '), "\0");
	else
		split_nodes_by_space(cmd_list);
	free((char *)command_line);
}
