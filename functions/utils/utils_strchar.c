/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:17:13 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:17:34 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*utils_strchar(char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (NULL);
	while (str[index])
	{
		if (str[index] == c)
			return (str + index);
		index++;
	}
	return (NULL);
}
