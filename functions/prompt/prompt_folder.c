/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_folder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:11:35 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 11:32:51 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	get_length(char *string)
{
	size_t	index;

	index = 0;
	while (string[index] != '\0')
		index++;
	return (index);
}

char	*prompt_folder(void)
{
	char	*buffer;
	char	*clone;
	size_t	index;

	buffer = smalloc(sizeof(char) * 4096);
	if (buffer == NULL)
		return (utils_strdup("minishell"));
	if (getcwd(buffer, 4096) == NULL)
		return (utils_strdup("minishell"));
	index = get_length(buffer) - 1;
	if (buffer[index] == '/' && buffer[index + 1] == '\0')
		return (utils_strdup("/"));
	while (index > 0)
	{
		if (buffer[index] == '/')
		{
			clone = utils_strdup(&(buffer[index + 1]));
			return (clone);
		}
		index--;
	}
	return (utils_strdup("minishell"));
}
