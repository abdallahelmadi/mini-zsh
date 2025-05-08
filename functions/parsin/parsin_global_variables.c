/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:03:43 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	while_loop_do(t_cmd_line **node)
{
	int (dbl), (sig), (index), (zindex);
	dbl = 0;
	sig = 0;
	index = -1;

	char	*location;
	char	*vraiblename;
	char	*p1;
	char	*p2;
	char	*p3;
	char	tempchar;

	if ((*node)->prev && utils_strstr_pro((*node)->prev->data, "<<"))
		return ;
	while (((*node)->data)[++index] != '\0')
	{
		if (((*node)->data)[index] == '\"' && sig != 1 && sig % 2 == 0)
			dbl++;
		else if (((*node)->data)[index] == '\'' && dbl != 1
			&& dbl % 2 == 0)
			sig++;
		location = utils_strstr_pro(&(((*node)->data)[index]), "$");
		if (location && (sig != 1 && sig % 2 == 0))
		{
			zindex = 1;
			location[0] = '\0';
			p1 = utils_strdup((*node)->data);
			location[0] = '$';

			if (location[zindex] == '\0' || location[zindex] == '-' || location[zindex] == ':' || location[zindex] == '*' || location[zindex] == '!' || location[zindex] == '\\' || location[zindex] == '+' || location[zindex] == ')' || location[zindex] == '(' || location[zindex] == '='
				|| location[zindex] == '"' || location[zindex] == '$' || location[zindex] == 6 || location[zindex] == '&' || location[zindex] == '^' || location[zindex] == '%' || location[zindex] == '#' || location[zindex] == '@')
				continue ;

			if (location[zindex] == '?')
			{
				(*node)->data = utils_strjoin(p1, utils_itoa(utils_getexit()), &(location[zindex + 1]));
				continue ;
			}

			while (location[zindex] != '\0' && location[zindex] != '-' && location[zindex] != ':' && location[zindex] != '*' && location[zindex] != '!' && location[zindex] != '\\' && location[zindex] != '+' && location[zindex] != ')' && location[zindex] != '(' && location[zindex] != '=' && location[zindex] != '?'
				&& location[zindex] != '$' && location[zindex] != '"' && location[zindex] != 6 && location[zindex] != '&' && location[zindex] != '^' && location[zindex] != '%' && location[zindex] != '#' && location[zindex] != '@')
				zindex++;

			tempchar = location[zindex];
			location[zindex] = '\0';
			vraiblename = utils_strdup(&(location[1]));
			location[zindex] = tempchar;

			p3 = utils_strdup(&(location[zindex]));

			p2 = utils_getenv(vraiblename);

			if (p2)
				(*node)->data = utils_strjoin(p1, p2, p3);
			else
				(*node)->data = utils_strjoin(p1, "", p3);


		}
	}
}

void	parsin_global_variables(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;

	tempnode = *cmd_list;
	while (tempnode)
	{
		while_loop_do(&tempnode);
		tempnode = tempnode->next;
	}
}
