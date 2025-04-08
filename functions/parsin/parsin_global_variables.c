/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/08 10:47:34 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_global_variables(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	int			simgle_quotes_counter;
	int			index;

	tempnode = *cmd_list;
	simgle_quotes_counter = 0;
	index = 0;
	while (tempnode != NULL)
	{
		while (tempnode->data[index] != '\0')
		{
			if (tempnode->data[index] == '\'')
				simgle_quotes_counter++;
			index++;
		}
		if (utils_strstr(tempnode->data, "$") && simgle_quotes_counter != 1
			&& simgle_quotes_counter % 2 == 0)
		{
			return ;
		}
		tempnode = tempnode->next;
	}
}
