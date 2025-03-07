/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 13:49:41 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	get_length(const char *string)
{
	size_t	index;

	index = 0;
	while (string[index] != '\0')
		index++;
	return (index);
}

char	*utils_strdup(const char *string)
{
	size_t	length;
	size_t	index;
	char	*clone;

	index = 0;
	length = get_length(string);
	clone = malloc(sizeof(char) * (length + 1));
	if (clone == NULL)
		return (NULL);
	while (string[index] != '\0')
	{
		clone[index] = string[index];
		index++;
	}
	clone[index] = '\0';
	return (clone);
}
