/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/13 15:58:02 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_empty_string(const char *command_line)
{
	int	index;

	index = 0;
	while (command_line[index] != '\0')
	{
		if (command_line[index] != ' ' && command_line[index] != '\t')
			return (SUCCESS);
		index++;
	}
	return (free((char *)command_line), FAILURE);
}

static void	tab2space(const char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '\t')
			((char *)string)[index] = ' ';
		index++;
	}
}

static void	small_logic(t_cmd_line **ttynode, t_cmd_line **t)
{
	(*ttynode) = utils_new_node("true");
	if ((*t)->prev && (*t)->prev->type != TP_PIPE)
		(*ttynode)->type = TP_STRING;
	else
		(*ttynode)->type = TP_CMD;
	(*ttynode)->next = (*t);
	(*ttynode)->prev = (*t)->prev;
	if ((*t)->prev)
		(*t)->prev->next = (*ttynode);
	(*t)->prev = (*ttynode);
}

static void	local_parsin_addnodes(t_cmd_line **cmd_list)
{
	t_cmd_line	*t;
	t_cmd_line	*ttynode;

	t = *cmd_list;
	while (t)
	{
		if (t->type == TP_REDIR1 || t->type == TP_REDIR11
			|| t->type == TP_REDIR2 || t->type == TP_REDIR22)
		{
			if (t->prev == NULL)
			{
				ttynode = utils_new_node("true");
				ttynode->type = TP_CMD;
				*cmd_list = ttynode;
				ttynode->next = t;
				t->prev = ttynode;
			}
			else if (t->prev == NULL || t->prev->type == TP_PIPE)
				small_logic(&ttynode, &t);
		}
		t = t->next;
	}
}

void	parsin_global(const char *command_line)
{
	t_cmd_line	*cmd_list;

	cmd_list = NULL;
	utils_setexit(SUCCESS);
	if (command_line[0] == '\0')
		return (free((char *)command_line));
	if (is_empty_string(command_line)
		|| parsin_forbidden_keywords(command_line)
		|| parsin_analyse_quotes(command_line))
		return ;
	tab2space(command_line);
	parsin_make_list(command_line, &cmd_list);
	parsin_global_variables(&cmd_list);
	parsin_tokenization(&cmd_list);
	parsin_syntax(&cmd_list);
	if (cmd_list == NULL)
		return ;
	parsin_switcher(&cmd_list);
	local_parsin_addnodes(&cmd_list);
	if (!parsin_heardoc_counter(&cmd_list))
		execution_global(&cmd_list);
}
