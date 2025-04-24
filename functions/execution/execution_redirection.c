/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/24 15:42:19 by bnafiai          ###   ########.fr       */
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
	t_cmd_line	*tmp;
	int			fd;
	char		*delimeter;
	char		*line ;
	char		*filename;
	char		**split;
	char		*end_str;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	sa_new.sa_handler = signal_handler_heredoc;
	sa_new.sa_flags = 0;
	sigemptyset(&sa_new.sa_mask);
	sigaction(SIGINT, &sa_new, &sa_old);
	tmp = node;
	tmp->next->data = utils_strjoin("/tmp/", tmp->next->data, "");
	delimeter = tmp->next->data;
	filename = delimeter;
	split = utils_split(delimeter, '/');
	end_str = utils_strjoin(split[1], "\n", "");
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while ((line = utils_get_next_line(0)))
	{
		if (utils_strcmp(line, end_str) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, utils_strlen(line));
		free(line);
	}
	free(end_str);
	utils_free(split);
	close(fd);
	if (g_global.g_signal == 1)
	{
		utils_setexit(SIGNAL_SIGINT);
		unlink(filename);
		sigaction(SIGINT, &sa_old, NULL);
		return;
	}

	fd = open(filename, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	sigaction(SIGINT, &sa_old, NULL);
}
// outfile << ms
// cat << l

