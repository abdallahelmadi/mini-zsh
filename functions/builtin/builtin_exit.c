/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/07 13:00:26 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_digit(char *string)
{
	int	index;

	index = 0;
	while (string[index] >= '0' && string[index] <= '9')
		index++;
	if (string[index] == '\0')
		return (SUCCESS);
	return (FAILURE);
}

void	builtin_exit(t_cmd_line *node)
{
	if (node->next && !is_digit(node->next->data) && node->next->next)
	{
		utils_setexit(FAILURE);
		printf("minishell: exit: too many arguments\n");
		return ;
	}
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
