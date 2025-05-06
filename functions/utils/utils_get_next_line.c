/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:19:04 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/06 10:13:22 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*my_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (utils_strdup(s2));
	if (!s2)
		return (utils_strdup(s1));
	total_len = utils_strlen(s1) + utils_strlen(s2) + 1;
	str = smalloc(total_len);
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

static char	*read_fd(int fd, char *stored)
{
	char	*str;
	ssize_t	sread;
	char	*new_one;

	str = smalloc(2);
	if (!str)
		return (NULL);
	sread = read(fd, str, 1);
	if (sread <= 0)
		return (NULL);
	str[sread] = '\0';
	new_one = my_strjoin(stored, str);
	return (new_one);
}

static char	*get_line(char *stored)
{
	char	*newline_ptr;
	size_t	index;
	char	*line;
	size_t	i;

	if (!stored || !*stored)
		return (NULL);
	newline_ptr = utils_strchar(stored, '\n');
	if (!newline_ptr)
		index = utils_strlen(stored);
	else
		index = newline_ptr - stored + 1;
	line = smalloc(index + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < index)
	{
		line[i] = stored[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stored(char *stored)
{
	char	*new_line;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	while (stored[i] != '\0' && stored[i] != '\n')
		i++;
	len = utils_strlen(stored) - i + 1;
	new_line = smalloc(len + 1);
	if (!new_line)
		return (NULL);
	j = 0;
	if (stored[i] == '\n')
		i++;
	while (stored[i] != '\0')
	{
		new_line[j] = stored[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*utils_get_next_line(int fd)
{
	static char		*stored;
	char			*line;
	char			*new_stored;

	while (!utils_strchar(stored, '\n'))
	{
		new_stored = read_fd(fd, stored);
		if (!new_stored)
			break ;
		stored = new_stored;
	}
	line = get_line(stored);
	if (!line)
		return (NULL);
	stored = update_stored(stored);
	if (stored && *stored == '\0')
		stored = NULL;
	return (line);
}
