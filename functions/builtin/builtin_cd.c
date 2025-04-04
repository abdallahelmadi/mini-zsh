/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 18:25:10 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_cd(t_cmd_line *node)
{
	char *path;
	struct stat path_stat;
	if (node->next)
		path = node->next->data;
	else
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd : home not set\n");
			return ;
		}
	}
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (chdir(path) != 0)
				perror("cd");
		}
		else
		{
			printf("cd: %s is not directory\n", path);
		}
	}
	else
	{
		perror("cd");
	}
}

