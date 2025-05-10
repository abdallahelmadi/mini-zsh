/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/10 20:33:56 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	write_to(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;

	tmp = node;
	fd = open(tmp->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->next->data, utils_strlen(tmp->next->data));
		write(2, "Permission denied\n", 18);
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	write_into(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;

	tmp = node;
	fd = open(tmp->next->data, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->next->data, utils_strlen(tmp->next->data));
		write(2, " Permission denied\n", 19);
		return (FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	read_from(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;

	tmp = node;
	fd = open(tmp->next->data, O_RDONLY, 0664);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, tmp->next->data, utils_strlen(tmp->next->data));
		write(2, " No such file or directory\n", 27);
		return (FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

static void	handle_for_signal(t_cmd_line *node)
{
	if (g_global.g_signal == 1)
	{
		utils_setexit(SIGNAL_SIGINT);
		unlink(node->next->data);
	}
}

void	read_to_delimeter(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;
	char		*line ;
	char		*end_str;

	g_global.g_signal = 0;
	setup_for_heredoc();
	tmp = node;
	end_str = utils_strjoin(tmp->next->data, "\n", "");
	tmp->next->data = utils_strdup("/tmp/hello_hr_6767");
	fd = open(tmp->next->data, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	line = utils_get_next_line(0);
	while (line)
	{
		if (g_global.g_signal == 1)
			break ;
		if (utils_strcmp(line, end_str) == 0)
			break ;
		write(fd, line, utils_strlen(line));
		line = utils_get_next_line(0);
	}
	close(fd);
	handle_for_signal(tmp);
}
