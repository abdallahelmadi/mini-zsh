/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_tokenization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:19:45 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/01 09:24:01 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_tokenization(t_cmd_line **cmd_list)
{
	return ;
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
// # define TP_FLAG 3
// # define TP_REDIR1 4
// # define TP_REDIR2 5
// # define TP_REDIR11 6
// # define TP_REDIR22 7
