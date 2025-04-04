/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:51:06 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/04 17:51:07 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_echo(t_cmd_line *node)
{
	t_cmd_line *tmp;
	int i = 1;
	if (node->next && utils_strcmp(node->next->data, "$?") == 0)
	{
		printf("%d\n", SUCCESS);
		return ;
	}
	tmp = node->next;
	if (tmp && utils_strcmp(tmp->data, "-n") == 0)
	{
		i = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		printf("%s", tmp->data);
		if (tmp->next)
			printf(" ");
		tmp = tmp->next;
	}
	if (i)
		printf("\n");
	utils_setexit(SUCCESS);
}
