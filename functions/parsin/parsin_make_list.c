/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:50:13 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/29 23:38:46 by abdael-m         ###   ########.fr       */
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
		lastnode = utils_last_node(list);
		newnode = utils_new_node(spliter);
		lastnode->next = newnode;
		newnode->prev = lastnode;
		lastnode = utils_last_node(list);
		newnode = utils_new_node(string[index]);
		lastnode->next = newnode;
		newnode->prev = lastnode;
		index++;
	}
	utils_free(string);
	return (list);
}

static void	split_command_p1(const char *command_line, t_cmd_line **cmd_list,
	const char *spliter)
{
	t_cmd_line	*tempnode;
	t_cmd_line	*tempnewlist;
	char		*tempchar;
	char		**tempdoublechar;

	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		if ((utils_strlen(spliter) == 1 && utils_strstr(command_line, spliter)
				&& utils_strstr(command_line, spliter)[1] != spliter[0]) || (
				utils_strlen(spliter) > 1
				&& utils_strstr(command_line, spliter)))
		{
			tempchar = utils_strjoin(" ", tempnode->data, " ");
			tempdoublechar = utils_split_pro(tempchar, (char *)spliter);
			free(tempchar);
			tempnewlist = fill_list(tempdoublechar, spliter);
			tempnode = utils_replace_node(&tempnode, &tempnewlist);
		}
		else
			tempnode = tempnode->next;
	}
}

static void	split_command_p0(const char *command_line, t_cmd_line **cmd_list,
	const char *spliter)
{
	char		*tempchar;
	char		**tempdoublechar;

	if (utils_strstr(command_line, spliter))
	{
		tempchar = utils_strjoin(" ", command_line, " ");
		tempdoublechar = utils_split_pro(tempchar, (char *)spliter);
		free(tempchar);
		*cmd_list = fill_list(tempdoublechar, spliter);
		split_command_p1(command_line, cmd_list, spliter);
	}
}

static void	split_command(const char *command_line, t_cmd_line **cmd_list,
		const char *spliter)
{
	if ((*cmd_list) == NULL)
		split_command_p0(command_line, cmd_list, spliter);
	else
		split_command_p1(command_line, cmd_list, spliter);
}

void	parsin_make_list(const char *command_line, t_cmd_line **cmd_list)
{
	split_command(command_line, cmd_list, "|");
	split_command(command_line, cmd_list, ">>");
	split_command(command_line, cmd_list, "<<");
	split_command(command_line, cmd_list, ">");
	split_command(command_line, cmd_list, "<");
}
