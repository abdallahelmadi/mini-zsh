/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:46:16 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/30 18:03:38 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	utils_free(char **string)
{
	int	index;

	index = 0;
	while (string[index] != NULL)
	{
		free(string[index]);
		index++;
	}
	free(string);
}

void	utils_free_list(t_cmd_line **list)
{
	t_cmd_line	*temp;

	while (*list != NULL)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->data);
		free(temp);
	}
}
