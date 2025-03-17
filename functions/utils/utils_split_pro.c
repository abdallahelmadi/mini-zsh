/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_pro.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:38:52 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/16 12:11:26 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	count_words(const char *string, char *c)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while (string[index] != '\0')
	{
		if (utils_strstr_pro(&(string[index]), c) && index != 0)
		{
			count++;
			index += utils_strlen(c);
		}
		else
			index++;
	}
	if (string[utils_strlen(string) - 1] != c[utils_strlen(c) - 1])
		count++;
	return (count);
}

static void	free_pointers(char **output)
{
	int	index;

	index = 0;
	while (output[index] != NULL)
	{
		free(output[index]);
		index++;
	}
	free(output);
	output = NULL;
}

static int	fill_pointers_while_part(const char *string, char **output,
	int *sindex, char *c)
{
	int	tindex;
	int	length;

	tindex = 0;
	length = 0;
	if (utils_strstr_pro(&(string[*sindex]), c))
		*sindex += utils_strlen(c);
	while (!utils_strstr_pro(&(string[*sindex + length]), c)
		&& string[*sindex + length] != '\0')
		length++;
	(*output) = (char *)malloc(sizeof(char) * (length + 1));
	if ((*output) == NULL)
		return (1);
	while (string[*sindex] != '\0' && !utils_strstr_pro(&(string[*sindex]), c))
	{
		(*output)[tindex] = string[*sindex];
		(*sindex)++;
		tindex++;
	}
	(*output)[tindex] = '\0';
	*sindex -= 1;
	return (0);
}

static void	fill_pointers(const char *string, char **output, char *c, int size)
{
	int	sindex;
	int	zindex;
	int	iindex;

	sindex = 0;
	zindex = 0;
	iindex = 0;
	while (string[sindex] != '\0' && size > iindex)
	{
		if (fill_pointers_while_part(string, &(output[zindex]), &sindex, c))
		{
			free_pointers(output);
			return ;
		}
		zindex++;
		if (string[sindex] != '\0')
			sindex++;
		iindex++;
	}
	output[zindex] = NULL;
}

char	**utils_split_pro(const char *string, char *c)
{
	char	**output;

	if (count_words(string, c) == 0)
		return (NULL);
	if (utils_strstr_pro(string, c)
		&& (utils_strstr_pro(string, c) + utils_strlen(c))[0] == '\0')
		return (NULL);
	output = (char **)malloc(sizeof(char *) * (count_words(string, c) + 1));
	if (output == NULL)
		return (NULL);
	fill_pointers(string, output, c, count_words(string, c));
	return (output);
}
