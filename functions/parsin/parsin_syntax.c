/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:57:05 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/10 11:56:31 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	near_pipe_err(t_cmd_line **cmd_list)
{
	printf("minishell: syntax error near unexpected token `|`\n");
	utils_setexit(SYNTAX_ERROR);
	*cmd_list = NULL;
	return ;
}

static void	near_line_err(t_cmd_line **cmd_list)
{
	printf("minishell: syntax error near unexpected token `newline`\n");
	utils_setexit(SYNTAX_ERROR);
	*cmd_list = NULL;
	return ;
}

void	parsin_syntax(t_cmd_line **cmd_list)
{
	t_cmd_line	*t;

	t = *cmd_list;
	if (t->type == TP_PIPE || utils_last_node(t)->type == TP_PIPE)
		return (near_pipe_err(cmd_list));
	while (t)
	{
		if ((t->type == TP_REDIR1 || t->type == TP_REDIR11
				|| t->type == TP_REDIR2 || t->type == TP_REDIR22)
			&& t->next == NULL)
			return (near_line_err(cmd_list));
		else if ((t->type == TP_REDIR1 || t->type == TP_REDIR11
				|| t->type == TP_REDIR2 || t->type == TP_REDIR22)
			&& t->next && (t->next->type == TP_PIPE
				|| t->next->type == TP_REDIR1 || t->next->type == TP_REDIR11
				|| t->next->type == TP_REDIR2 || t->next->type == TP_REDIR22))
		{
			printf("minishell: syntax error near unexpected token `%s`\n",
				t->next->data);
			utils_setexit(SYNTAX_ERROR);
			*cmd_list = NULL;
			return ;
		}
		t = t->next;
	}
}
