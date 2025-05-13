/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_heardoc_counter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:53:14 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/13 15:57:54 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsin_heardoc_counter(t_cmd_line **list)
{
	t_cmd_line	*temp;
	int			index;

	temp = *list;
	index = 0;
	while (temp)
	{
		if (temp->type == TP_REDIR22)
			index++;
		temp = temp->next;
	}
	if (index > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		utils_setexit(2);
		return (1);
	}
	return (0);
}
