/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:57:05 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/21 12:13:04 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_syntax(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;

	tempnode = *cmd_list;
	while (tempnode)
	{
		if ((tempnode->type == TP_REDIR1 || tempnode->type == TP_REDIR11
			|| tempnode->type == TP_REDIR2 || tempnode->type == TP_REDIR22)
			&& tempnode->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `newline`\n");
			utils_setexit(SYNTAX_ERROR);
			utils_free_list(cmd_list);
			*cmd_list = NULL;
			return ;
		}
		else if ((tempnode->type == TP_REDIR1 || tempnode->type == TP_REDIR11
			|| tempnode->type == TP_REDIR2 || tempnode->type == TP_REDIR22)
			&& tempnode->next && (tempnode->next->type == TP_PIPE
			|| tempnode->next->type == TP_REDIR1 || tempnode->next->type == TP_REDIR11
			|| tempnode->next->type == TP_REDIR2 || tempnode->next->type == TP_REDIR22))
		{
			printf("minishell: syntax error near unexpected token `%s`\n", tempnode->next->data);
			utils_setexit(SYNTAX_ERROR);
			utils_free_list(cmd_list);
			*cmd_list = NULL;
			return ;
		}
		tempnode = tempnode->next;
	}
}
