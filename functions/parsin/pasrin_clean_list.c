/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasrin_clean_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:46:29 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/31 10:56:57 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	empty_node(t_cmd_line *node)
{
	int	index;

	index = 0;
	while (node->data[index] != '\0')
	{
		if ((node->data)[index] != ' ')
			return (SUCCESS);
		index++;
	}
	return (FAILURE);
}

static void	clean_node_next_part(t_cmd_line *node, char **newaddress,
	int length)
{
	int		index;
	char	*newstring;

	index = length - 1;
	while ((node->data)[index] == ' ')
	{
		(node->data)[index] = '\0';
		index--;
	}
	newstring = utils_strdup(*newaddress);
	free(node->data);
	node->data = newstring;
}

static void	clean_node(t_cmd_line *node)
{
	int		length;
	int		index;
	char	*newaddress;

	length = utils_strlen(node->data);
	newaddress = node->data;
	index = 0;
	if ((node->data)[0] == ' ' || (node->data)[length - 1] == ' ')
	{
		while ((node->data)[index] == ' ')
		{
			newaddress = &((node->data)[index + 1]);
			index++;
		}
	}
	clean_node_next_part(node, &newaddress, length);
}

void	pasrin_clean_list(t_cmd_line **list)
{
	t_cmd_line	*tempnode;

	tempnode = *list;
	while (tempnode != NULL)
	{
		if (empty_node(tempnode))
			utils_delete_node(&tempnode);
		else
			clean_node(tempnode);
		tempnode = tempnode->next;
	}
}
