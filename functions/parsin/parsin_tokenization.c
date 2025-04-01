/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:19:45 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/01 18:11:36 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_origin_data_quotes(t_cmd_line **node)
{
	int	index;

	index = 0;
	while (((*node)->data)[index] != '\0')
	{
		if (((*node)->data)[index] == 1)
			((*node)->data)[index] = '|';
		else if (((*node)->data)[index] == 2)
		{
			((*node)->data)[index++] = '>';
			((*node)->data)[index] = '>';
		}
		else if (((*node)->data)[index] == 3)
		{
			((*node)->data)[index++] = '<';
			((*node)->data)[index] = '<';
		}
		else if (((*node)->data)[index] == 4)
			((*node)->data)[index] = '<';
		else if (((*node)->data)[index] == 5)
			((*node)->data)[index] = '>';
		else if (((*node)->data)[index] == 6)
			((*node)->data)[index] = ' ';
		index++;
	}
}

static void	add_token(t_cmd_line **node)
{
	if (utils_strstr_pro((*node)->data, "|"))
		(*node)->type = TP_PIPE;
	else if (utils_strstr_pro((*node)->data, ">>"))
		(*node)->type = TP_REDIR11;
	else if (utils_strstr_pro((*node)->data, "<<"))
		(*node)->type = TP_REDIR22;
	else if (utils_strstr_pro((*node)->data, ">"))
		(*node)->type = TP_REDIR1;
	else if (utils_strstr_pro((*node)->data, "<"))
		(*node)->type = TP_REDIR2;
	else
	{
		if ((*node)->prev == NULL)
			(*node)->type = TP_CMD;
		else if (((*node)->prev)->type == TP_REDIR2
			|| ((*node)->prev)->type == TP_REDIR1
			|| ((*node)->prev)->type == TP_REDIR11)
			(*node)->type = TP_PATH;
		else if (((*node)->prev)->type == TP_CMD
			|| ((*node)->prev)->type == TP_STRING
			|| ((*node)->prev)->type == TP_REDIR22)
			(*node)->type = TP_STRING;
		else
			(*node)->type = TP_CMD;
	}
}

static void	remove_qoutes(t_cmd_line **node)
{
	(void)node;
	return ;
}

void	parsin_tokenization(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;

	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		reset_origin_data_quotes(&tempnode);
		add_token(&tempnode);
		remove_qoutes(&tempnode);
		tempnode = tempnode->next;
	}
}
