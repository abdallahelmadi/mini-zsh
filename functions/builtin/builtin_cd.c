/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/09 16:23:21 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	builtin_cd_run(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (access(path, R_OK) == 0)
			{
				chdir(path);
				utils_setexit(SUCCESS);
			}
			else
				return (printf("minishell: cd: %s: Permission denied\n", path),
					utils_setexit(FAILURE));
		}
		else
			return (printf("minishell: cd: %s: Not directory\n", path),
				utils_setexit(FAILURE));
	}
	else
		return (printf("minishell: cd: %s: No such file or directory\n",
				path), utils_setexit(FAILURE));
}

void	builtin_cd(t_cmd_line *node)
{
	char	*path;

	if (node->next == NULL || (node->next && node->next->type != TP_STRING))
	{
		path = utils_getenv("HOME");
		if (path == NULL)
			return (printf("minishell: cd: HOME not set\n"),
				utils_setexit(FAILURE));
	}
	else if ((node->next && node->next->type == TP_STRING)
		&& (node->next->next && node->next->next->type == TP_STRING))
		return (printf("minishell: cd: Too many arguments\n"),
			utils_setexit(FAILURE));
	else if (node->next)
		path = node->next->data;
	else
		path = "/home";
	builtin_cd_run(path);
}
