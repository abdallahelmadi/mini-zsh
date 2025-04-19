/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/18 16:33:45 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsin_global_variables(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	char		*position;
	int			index;
	int			counter;

	tempnode = *cmd_list;
	while (tempnode)
	{
		position = utils_strstr(tempnode->data, "$");
		index = 0;
		counter = 0;
		if (position)
		{
			while ((tempnode->data)[index] != *position)
			{
				if ((tempnode->data)[index] == '\'')
					counter++;
				index++;
			}
			if (counter == 1 || counter % 2 == 1)
				break ;
		}
		else
			tempnode = tempnode->next;
	}
}
