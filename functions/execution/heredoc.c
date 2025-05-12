/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:45:52 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/12 19:54:47 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_for_signal(t_cmd_line *node)
{
	if (g_global.g_signal == 1)
	{
		utils_setexit(SIGNAL_SIGINT);
		unlink(node->next->data);
	}
}

static char	*generate_filename(void)
{
	char		*filename;
	char		*num;
	static int	heredoc_count = 0;

	num = utils_itoa(heredoc_count++);
	if (!num)
		return (NULL);
	filename = utils_strjoin("/tmp/heredoc_", num, "");
	return (filename);
}

static void	write_line_loop(int fd, char *end_str)
{
	char	*line;

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
}

void	read_to_delimeter(t_cmd_line *node)
{
	t_cmd_line	*tmp;
	int			fd;
	char		*end_str;
	char		*tempfile;

	g_global.g_signal = 0;
	setup_for_heredoc();
	tmp = node;
	end_str = utils_strjoin(tmp->next->data, "\n", "");
	tempfile = generate_filename();
	tmp->next->data = tempfile;
	fd = open(tmp->next->data, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	write_line_loop(fd, end_str);
	handle_for_signal(tmp);
}
