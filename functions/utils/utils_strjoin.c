/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:24:41 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 14:48:41 by abdael-m         ###   ########.fr       */
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

char	*utils_strjoin(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	int		index;

	result = malloc(sizeof(char) * (get_length(s1) + get_length(s2)
				+ get_length(s3) + 1));
	if (result == NULL)
		return (NULL);
	index = -1;
	while (s1[++index] != '\0')
		result[index] = s1[index];
	index = -1;
	while (s2[++index] != '\0')
		result[get_length(s1) + index] = s2[index];
	index = -1;
	while (s3[++index] != '\0')
		result[get_length(s1) + get_length(s2) + index] = s3[index];
	result[get_length(s1) + get_length(s2) + index] = '\0';
	return (result);
}
