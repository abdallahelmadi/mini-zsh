/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:24:41 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/13 19:20:15 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*utils_strjoin(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	int		index;

	result = malloc(sizeof(char) * (utils_strlen(s1) + utils_strlen(s2)
				+ utils_strlen(s3) + 1));
	if (result == NULL)
		return (NULL);
	index = -1;
	while (s1[++index] != '\0')
		result[index] = s1[index];
	index = -1;
	while (s2[++index] != '\0')
		result[utils_strlen(s1) + index] = s2[index];
	index = -1;
	while (s3[++index] != '\0')
		result[utils_strlen(s1) + utils_strlen(s2) + index] = s3[index];
	result[utils_strlen(s1) + utils_strlen(s2) + index] = '\0';
	return (result);
}
