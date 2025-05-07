/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/07 13:51:16 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	write_to(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;

	fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		printf("miniahell: %s: Permission denied\n", tmp->next->data);
		return (FAILURE);
	}
	dup2(fd , STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	write_into(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;
	fd = open(tmp->next->data, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (fd == -1)
	{
		printf("minishell: %s: Permission denied\n", tmp->next->data);
		return (FAILURE);
	}
	dup2(fd , STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	read_from(t_cmd_line *node)
{
	t_cmd_line *tmp = node;
	int	fd;
	fd = open(tmp->next->data, O_RDONLY, 0664);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", tmp->next->data);
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

void	read_to_delimeter(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;
	char		*line ;
	// char		**split;
	char		*end_str;

	g_global.g_signal = 0;
	setup_for_heredoc();
	tmp = node;
	end_str = utils_strjoin(tmp->next->data, "\n", "");
	tmp->next->data = utils_strdup("/tmp/hello_hr_6767");
	// split = utils_split(tmp->next->data, '/');
	fd = open(tmp->next->data, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	while ((line = utils_get_next_line(0)))
	{
		if (g_global.g_signal == 1)
			break ;
		if (utils_strcmp(line, end_str) == 0)
			break;
		write(fd, line, utils_strlen(line));
		free(line);
	}
	close(fd);
	if (g_global.g_signal == 1)
	{
		close(fd);
		utils_setexit(SIGNAL_SIGINT);
		unlink(tmp->next->data);
		restore();
		return;
	}
	fd = open(tmp->next->data, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}
// int	read_heredoc_file(t_cmd_line *node)
// {
// 	int	fd;
// 	fd = open(node->next->data, O_RDONLY);
// 	if (fd == -1)
// 		return (FAILURE);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 	{
// 		close(fd);
// 		return (FAILURE);
// 	}
// 	close(fd);
// 	return (SUCCESS);
// }
