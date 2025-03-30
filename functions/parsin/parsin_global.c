/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/30 18:03:27 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_global(const char *command_line)
{
	t_cmd_line	*cmd_list;

	cmd_list = NULL;
	g_lastexitstatus = SUCCESS;
	if (command_line[0] == '\0')
		return (free((char *)command_line));
	if (parsin_forbidden_keywords(command_line)
		|| parsin_analyse_quotes(command_line))
		return ;
	parsin_make_list(command_line, &cmd_list);
	utils_free_list(&cmd_list);
}

// value of some characeters inside quotes after use parsin_analyse_quotes
// |   : 1
// >>  : 2
// <<  : 3
// <   : 4
// >   : 5
// ' ' : 6
// value of nodes type after tokenization
// # define TP_CMD 0
// # define TP_PIPE 1
// # define TP_STRING 2
// # define TP_REDIR1 3
// # define TP_REDIR2 4
// # define TP_REDIR11 5
// # define TP_REDIR22 6
