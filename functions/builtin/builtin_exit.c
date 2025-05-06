/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:43:20 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_exit(t_cmd_line *node)
{
	while (node->next && node->next->type == TP_STRING)
		node = node->next;
	if (node->next && node->next->type == TP_PIPE)
		return ;
	while (node->prev != NULL)
		node = node->prev;
	smalloc(-1);
	printf("exit\n");
	rl_clear_history();
	exit(SUCCESS);
}
