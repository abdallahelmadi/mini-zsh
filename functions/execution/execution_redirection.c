/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:23:15 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/09 20:54:10 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_to(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;

	fd = open(node->next->data, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void	write_into(t_cmd_line *node)
{
	t_cmd_line	*tmp = node;
	int	fd;
	fd = open(node->next->data, O_CREAT | O_APPEND | O_WRONLY, 0666);
	dup2(fd , STDOUT_FILENO);
	close(fd);
}

void	read_from(t_cmd_line *node)
{
	t_cmd_line *tmp = node;
	int	fd;
	fd = open(node->next->data, O_RDONLY, 0666);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
// ls < outfile
