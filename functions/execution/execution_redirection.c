/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/11 19:04:51 by bnafiai          ###   ########.fr       */
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
// void	read_to_delimeter(t_cmd_line *node)
// {
// 	// getnextline()
// 	t_cmd_line *tmp = node;
// 	int		fd;
// 	char	*line = get_next_line(0);
// 	char	*file = ".mini-zsh";
// 	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
// 	while (line && utils_strcmp(line, node->next->data))
// 	{
// 		write(fd, line, utils_strlen(line));
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	close(fd);
// 	int fd2 = open(file, O_RDONLY, 0664);
// 	dup2(fd2, 0);
// 	close(fd2);
// }
// outfile << ms

