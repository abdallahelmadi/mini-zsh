/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:29:34 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:18:28 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*utils_strstr(const char *string, const char *search)
{
	int	index;
	int	zndex;

	index = 0;
	while (string[index] != '\0')
	{
		zndex = 0;
		if (string[index] == search[0])
		{
			while (search[zndex] != '\0' && string[index + zndex] != '\0')
			{
				if (string[index + zndex] == search[zndex])
					zndex++;
				else
					break ;
			}
			if (search[zndex] == '\0')
				return ((char *)(&(string[index])));
		}
		index++;
	}
	return (NULL);
}
