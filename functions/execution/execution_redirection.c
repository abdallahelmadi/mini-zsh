/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/14 20:30:48 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_to(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;

	fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void	write_into(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;
	fd = open(tmp->next->data, O_CREAT | O_APPEND | O_WRONLY, 0664);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void	read_from(t_cmd_line *node)
{
	t_cmd_line *tmp = node;
	int	fd;
	fd = open(tmp->next->data, O_RDONLY, 0664);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
// ls < outfile
void	read_to_delimeter(t_cmd_line *node)
{
	// getnextline()
	t_cmd_line *tmp = node;
	int		fd;
	char	*delimeter;
	char	*line ;
	char	*filename;

	tmp->next->data = utils_strjoin("/tmp/", tmp->next->data, "");
	delimeter = tmp->next->data;
	filename = delimeter;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while ((line = utils_get_next_line(0)))
	{
		if (utils_strcmp(line, utils_strjoin(utils_split(
			delimeter,
			'/'
		)[1], "\n", "")) == 0)
			break;
		printf("Heredoc>");
		write(fd, line, utils_strlen(line));
		free(line);
	}
	fd = open(filename, O_RDONLY);
	dup2(fd, 0);
}
// outfile << ms

