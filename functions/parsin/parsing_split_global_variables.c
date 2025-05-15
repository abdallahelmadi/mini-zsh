/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split_global_variables.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:11:22 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/15 17:40:06 by abdael-m         ###   ########.fr       */
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
	return (list);
}

void	parsing_split_global_variables(t_cmd_line **list)
{
	t_cmd_line	*temp;
	t_cmd_line	*new_list;
	char		**spliters;

	temp = *list;
	while (temp)
	{
		if (utils_strstr(temp->data, " "))
		{
			spliters = utils_split(temp->data, ' ');
			new_list = fill_list(spliters, "\0");
			utils_replace_node(list, &temp, &new_list);
		}
		temp = temp->next;
	}
}
