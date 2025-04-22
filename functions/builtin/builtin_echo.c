/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:51:06 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/18 14:34:47 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_echo(t_cmd_line *node)
{
	t_cmd_line	*temp;
	int			newlinestatus;

	temp = node->next;
	newlinestatus = 1;
	if (temp != NULL && temp->type == TP_STRING
		&& utils_strcmp(temp->data, "-n") == 0)
	{
		newlinestatus = 0;
		temp = temp->next;
	}
	while (temp != NULL && temp->type == TP_STRING)
	{
		printf("%s", temp->data);
		if (temp->next)
			write(1, " ", 1);
		temp = temp->next;
	}
	if (newlinestatus)
		printf("\n");
	utils_setexit(SUCCESS);
}
