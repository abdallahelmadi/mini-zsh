/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_heardoc_counter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:53:14 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/14 10:05:05 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	remove_empty_nodes_again(t_cmd_line **list)
{
	t_cmd_line	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->data[0] == '\0')
		{
			utils_delete_node(list, &temp);
			temp = *list;
		}
		else
			temp = temp->next;
	}
	if (*list == NULL)
		return (1);
	return (0);
}

int	parsin_heardoc_counter(t_cmd_line **list)
{
	t_cmd_line	*temp;
	int			index;

	temp = *list;
	index = 0;
	while (temp)
	{
		if (temp->type == TP_REDIR22)
			index++;
		temp = temp->next;
	}
	if (index > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		utils_setexit(2);
		return (1);
	}
	if (remove_empty_nodes_again(list))
		return (1);
	return (0);
}
