/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:19:45 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/12 14:55:25 by abdael-m         ###   ########.fr       */
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
			|| ((*node)->prev)->type == TP_REDIR22
			|| (*node)->prev->type == TP_PATH)
			(*node)->type = TP_STRING;
		else
			(*node)->type = TP_CMD;
	}
}

static char	*special_strdup(char *string)
{
	char	*newstring;
	int		index;
	int		indexofnewsreing;

	newstring = (char *)malloc(sizeof(char) * utils_strlen(string) + 1);
	if (newstring == NULL)
		return (NULL);
	index = 0;
	indexofnewsreing = 0;
	while (string[index] != '\0')
	{
		if (string[index] == 1)
			index++;
		else
		{
			newstring[indexofnewsreing] = string[index];
			index++;
			indexofnewsreing++;
		}
	}
	newstring[indexofnewsreing] = '\0';
	free(string);
	return (newstring);
}

static void	remove_qoutes(t_cmd_line **node, int *index)
{
	int (dbl), (sig);
	dbl = 0;
	sig = 0;
	while (((*node)->data)[++(*index)] != '\0')
	{
		if (((*node)->data)[(*index)] == '\"' && sig != 1 && sig % 2 == 0)
		{
			((*node)->data)[(*index)] = 1;
			dbl++;
		}
		else if (((*node)->data)[(*index)] == '\'' && dbl != 1
			&& dbl % 2 == 0)
		{
			((*node)->data)[(*index)] = 1;
			sig++;
		}
		if (utils_strstr_pro(&(((*node)->data)[*index]), "$?")
			&& (dbl == 1 || dbl % 2 == 1
				|| (sig % 2 == 0 && dbl % 2 == 0)))
		{
			((*node)->data)[(*index)] = 2;
			((*node)->data)[(*index) + 1] = 2;
		}
	}
	(*node)->data = special_strdup((*node)->data);
}

void	parsin_tokenization(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	int			index;

	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		index = -1;
		reset_origin_data_quotes(&tempnode);
		add_token(&tempnode);
		remove_qoutes(&tempnode, &index);
		tempnode = tempnode->next;
	}
}
