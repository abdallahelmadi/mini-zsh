/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/12 19:48:20 by bnafiai          ###   ########.fr       */
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
