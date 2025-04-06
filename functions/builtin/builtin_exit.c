/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/06 10:21:03 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_exit(t_cmd_line *node)
{
	while (node->next && node->next->type == TP_STRING)
		node = node->next;
	if (node->next && node->next->type == TP_PIPE)
		return ;
	utils_free(utils_gsetenv(NULL));
	while (node->prev != NULL)
		node = node->prev;
	utils_free_list(&node);
	printf("exit\n");
	exit(SUCCESS);
}
