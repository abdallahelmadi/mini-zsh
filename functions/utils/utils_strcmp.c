/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:39:54 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/13 15:07:03 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	utils_strcmp(const char *string, char c)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] == c)
			return (SUCCESS);
		index++;
	}
	return (FAILURE);
}
