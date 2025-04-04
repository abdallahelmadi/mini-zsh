/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:42:17 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 13:18:08 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_next_type(t_cmd_line *tempnode)
{
	if ((tempnode->next)->type == TP_REDIR1
		|| (tempnode->next)->type == TP_REDIR2
		|| (tempnode->next)->type == TP_REDIR11
		|| (tempnode->next)->type == TP_REDIR22)
		return (FAILURE);
	return (SUCCESS);
}

int	execution_syntax(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;

	if ((*cmd_list)->type == TP_PIPE
		|| utils_last_node(*cmd_list)->type == TP_PIPE)
		return (printf("minishell: syntax error, near unexpected token `|`\n"),
			utils_setexit(SYNTAX_ERROR), utils_free_list(cmd_list), FAILURE);
	tempnode = *cmd_list;
	while (tempnode != NULL)
	{
		if (tempnode->type == TP_REDIR1 || tempnode->type == TP_REDIR2
			|| tempnode->type == TP_REDIR11 || tempnode->type == TP_REDIR22)
		{
			if (tempnode->next == NULL)
				return (utils_setexit(SYNTAX_ERROR), utils_free_list(cmd_list),
					printf("minishell: %s token `newline`\n",
						"syntax error, near unexpected"), FAILURE);
			if (check_next_type(tempnode) || (tempnode->next)->type == TP_PIPE)
				return (printf("minishell: syntax error, %s`%s`\n",
						"near unexpected token ", (tempnode->next)->data),
					utils_setexit(SYNTAX_ERROR), utils_free_list(cmd_list),
					FAILURE);
		}
		tempnode = tempnode->next;
	}
	return (SUCCESS);
}
