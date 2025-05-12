/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/12 14:02:26 by abdael-m         ###   ########.fr       */
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

static void	function_of_loop(char *lct, char **part, int *i,
	t_cmd_line **node)
{
	char	tempchar;
	char	*vraiblename;

	lct[0] = '\0';
	part[0] = utils_strdup((*node)->data);
	lct[0] = '$';
	if (!is_alphanum(lct[(*i)]) && lct[(*i)] != '_' && lct[(*i)] != '?')
		return ;
	if (lct[(*i)] == '?')
	{
		(*node)->data = utils_strjoin(part[0],
				utils_itoa(utils_getexit()), &(lct[(*i) + 1]));
		return ;
	}
	while (is_alphanum(lct[(*i)]) || lct[(*i)] == '_')
		(*i)++;
	tempchar = lct[(*i)];
	lct[(*i)] = '\0';
	vraiblename = utils_strdup(&(lct[1]));
	lct[(*i)] = tempchar;
	part[2] = utils_strdup(&(lct[(*i)]));
	part[1] = utils_getenv(vraiblename);
	(*node)->data = utils_strjoin(part[0], "", part[2]);
	if (part[1])
		(*node)->data = utils_strjoin(part[0], part[1], part[2]);
}

static void	while_loop_do(t_cmd_line **node, int *zindex, int *index)
{
	int		dbl;
	int		sig;
	char	*location;
	char	*part[3];

	dbl = 0;
	sig = 0;
	if ((*node)->prev && utils_strstr_pro((*node)->prev->data, "<<"))
		return ;
	while (((*node)->data)[++(*index)] != '\0')
	{
		if (((*node)->data)[(*index)] == '\"' && sig != 1 && sig % 2 == 0)
			dbl++;
		else if (((*node)->data)[(*index)] == '\'' && dbl != 1
			&& dbl % 2 == 0)
			sig++;
		location = utils_strstr_pro(&(((*node)->data)[(*index)]), "$");
		if (location && (sig != 1 && sig % 2 == 0))
			function_of_loop(location, part, zindex, node);
	}
}

void	parsin_global_variables(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	int			index;
	int			zindex;

	tempnode = *cmd_list;
	while (tempnode)
	{
		index = -1;
		zindex = 1;
		while_loop_do(&tempnode, &zindex, &index);
		tempnode = tempnode->next;
	}
}
