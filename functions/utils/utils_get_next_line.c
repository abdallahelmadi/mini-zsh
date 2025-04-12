#include <minishell.h>
static char	*my_strchar(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return (NULL);
}

static size_t	my_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*my_strdup(char *s)
{
	size_t	i;
	char	*dup;
	size_t	len;

	i = 0;
	len = my_strlen(s) + 1;
	dup = malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
static char	*my_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (my_strdup(s2));
	if (!s2)
		return (my_strdup(s1));
	total_len = my_strlen(s1) + my_strlen(s2) + 1;
	str = malloc(total_len);
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

	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	sread = read(fd, str, BUFFER_SIZE);
	if (sread <= 0)
	{
		free(str);
		return (NULL);
	}
	str[sread] = '\0';
	new_one = my_strjoin(stored, str);
	free(stored);
	free(str);
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
	newline_ptr = my_strchar(stored, '\n');
	if (!newline_ptr)
		index = my_strlen(stored);
	else
		index = newline_ptr - stored + 1;
	line = malloc(index + 1);
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
	len = my_strlen(stored) - i + 1;
	new_line = malloc(len + 1);
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
	free(stored);
	return (new_line);
}

char	*utils_get_next_line(int fd)
{
	static char		*stored;
	char			*line;
	char			*new_stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!my_strchar(stored, '\n'))
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
	{
		free(stored);
		stored = NULL;
	}
	return (line);
}
