/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/11 11:51:53 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_alphanum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static void	while_loop_do(t_cmd_line **node)
{
	int		dbl;
	int		sig;
	int		index;
	int		zindex;
	char	*location;
	char	*vraiblename;
	char	*part[3];
	char	tempchar;
	
	dbl = 0;
	sig = 0;
	index = -1;
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
			part[0] = utils_strdup((*node)->data);
			location[0] = '$';
			if (!is_alphanum(location[zindex]) && location[zindex] != '_')
				continue ;
			if (location[zindex] == '?')
			{
				(*node)->data = utils_strjoin(part[0],
					utils_itoa(utils_getexit()), &(location[zindex + 1]));
				continue ;
			}
			while (is_alphanum(location[zindex]) || location[zindex] == '_')
				zindex++;
			tempchar = location[zindex];
			location[zindex] = '\0';
			vraiblename = utils_strdup(&(location[1]));
			location[zindex] = tempchar;
			part[2] = utils_strdup(&(location[zindex]));
			part[1] = utils_getenv(vraiblename);
			if (part[1])
				(*node)->data = utils_strjoin(part[0], part[1], part[2]);
			else
				(*node)->data = utils_strjoin(part[0], "", part[2]);
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
