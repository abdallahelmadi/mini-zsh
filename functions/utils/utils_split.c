/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:56:07 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/23 14:16:00 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	count_words(const char *string, char c)
{
	int		index;
	size_t	count;

	index = 0;
	count = 0;
	while (string[index] != '\0')
	{
		if ((index == 0 || string[index - 1] == c) && string[index] != c)
			count++;
		index++;
	}
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
	int *sindex, char c)
{
	int	tindex;
	int	length;

	tindex = 0;
	length = 0;
	while (string[*sindex + length] != c
		&& string[*sindex + length] != '\0')
		length++;
	(*output) = (char *)malloc(sizeof(char) * (length + 1));
	if ((*output) == NULL)
		return (1);
	while (string[*sindex] != '\0' && string[*sindex] != c)
	{
		(*output)[tindex] = string[*sindex];
		(*sindex)++;
		tindex++;
	}
	(*output)[tindex] = '\0';
	return (0);
}

static void	fill_pointers(const char *string, char **output, char c)
{
	int	sindex;
	int	zindex;

	sindex = 0;
	zindex = 0;
	while (string[sindex] != '\0')
	{
		while (string[sindex] == c)
			sindex++;
		if (string[sindex] != '\0')
		{
			if (fill_pointers_while_part(string, &(output[zindex]), &sindex, c))
			{
				free_pointers(output);
				return ;
			}
			zindex++;
		}
		if (string[sindex] != '\0')
			sindex++;
	}
	output[zindex] = NULL;
}

char	**utils_split(const char *string, char c)
{
	char	**output;

	if (count_words(string, c) == 0)
		return (NULL);
	output = (char **)malloc(sizeof(char *) * (count_words(string, c) + 1));
	if (output == NULL)
		return (NULL);
	fill_pointers(string, output, c);
	return (output);
}
