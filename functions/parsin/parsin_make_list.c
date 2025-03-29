/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:50:13 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/29 16:45:32 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	*fill_list(char **string, char *spliter)
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

static void	split_command(const char *command_line, t_cmd_line **cmd_list,
		const char *spliter)
{
	if ((*cmd_list) == NULL)
	{
		return ;
	}
	else
	{
		return ;
	}
}

void	parsin_make_list(const char *command_line, t_cmd_line **cmd_list)
{
	split_command(command_line, cmd_list, "|");
	split_command(command_line, cmd_list, ">>");
	split_command(command_line, cmd_list, "<<");
	split_command(command_line, cmd_list, ">");
	split_command(command_line, cmd_list, "<");
}

// static void	split_and_relink_command(const char *command_line,
// 				t_cmd_line **globalnode, char *spliter)
// {
// 	char		*new_command_line;
// 	char		**tempofsplitv0;
// 	t_cmd_line	*tempnode;
// 	t_cmd_line	*tempnodeofnewlist;
// 	if (utils_strlen(spliter) > 1 && utils_strstr(command_line, spliter))
// 	{
// 		new_command_line = utils_strjoin(" ", command_line, " ");
// 		if (*globalnode == NULL)
// 		{
// 			tempofsplitv0 = utils_split_pro(new_command_line, spliter);
// 			if (tempofsplitv0 == NULL)
// 				return ;
// 			*globalnode = fill_list(tempofsplitv0, spliter);
// 			free(new_command_line);
// 			utils_free(tempofsplitv0);
// 		}
// 		else if (*globalnode != NULL)
// 		{
// 			tempnode = *globalnode;
// 			while (tempnode != NULL)
// 			{
// 				if (utils_strstr(tempnode->data, spliter))
// 				{
// 					new_command_line = utils_strjoin(" ", tempnode->data, " ");
// 					tempofsplitv0 = utils_split_pro(new_command_line, spliter);
// 					free(new_command_line);
// 					if (tempofsplitv0 == NULL)
// 						return ;
// 					tempnodeofnewlist = fill_list(tempofsplitv0, spliter);
// 					free(tempofsplitv0);
// 					*globalnode = utils_replace_node(globalnode, &tempnode, 
//						&tempnodeofnewlist);
// 				}
// 				tempnode = tempnode->next;
// 			}
// 		}
// 	}
// 	else if (utils_strlen(spliter) == 1)
// 	{
// 		if (*globalnode != NULL)
// 		{
// 			tempnode = *globalnode;
// 			while (tempnode != NULL)
// 			{
// 				if (utils_strstr(tempnode->data, spliter) 
//					&& utils_strstr(tempnode->data, spliter)[1] != spliter[0])
// 				{
// 					new_command_line = utils_strjoin(" ", tempnode->data, " ");
// 					tempofsplitv0 = utils_split_pro(new_command_line, spliter);
// 					free(new_command_line);
// 					if (tempofsplitv0 == NULL)
// 						return ;
// 					tempnodeofnewlist = fill_list(tempofsplitv0, spliter);
// 					free(tempofsplitv0);
// 					*globalnode = utils_replace_node(globalnode,
//							&tempnode, &tempnodeofnewlist);
// 				}
// 				tempnode = tempnode->next;
// 			}
// 		}
// 		else
// 		{
// 			new_command_line = utils_strjoin(" ", command_line, " ");
// 			tempofsplitv0 = utils_split(new_command_line, spliter[0]);
// 			if (tempofsplitv0 == NULL)
// 				return ;
// 			*globalnode = fill_list(tempofsplitv0, spliter);
// 			free(new_command_line);
// 			utils_free(tempofsplitv0);
// 		}
// 	}
// }
// static t_cmd_line	*split_command_as_list(const char *command_line)
// {
// 	t_cmd_line	*globalnode;
// 	char		*new_command_line;
// 	char		**tempofsplitv0;
// 	globalnode = NULL;
// 	new_command_line = utils_strjoin(" ", command_line, " ");
// 	if (utils_strstr(new_command_line, "|"))
// 	{
// 		tempofsplitv0 = utils_split(new_command_line, '|');
// 		if (tempofsplitv0 == NULL)
// 			return (NULL);
// 		globalnode = fill_list(tempofsplitv0, "|");
// 		free(new_command_line);
// 		utils_free(tempofsplitv0);
// 	}
// 	split_and_relink_command(command_line, &globalnode, ">>");
// 	split_and_relink_command(command_line, &globalnode, "<<");
// 	split_and_relink_command(command_line, &globalnode, ">");
// 	split_and_relink_command(command_line, &globalnode, "<");
// 	return (globalnode);
// }
