/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/10 15:35:25 by bnafiai          ###   ########.fr       */
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
			if (access(path, X_OK) == 0)
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

static void	update_var_for_cd(char **env, char *key, char *new_value)
{
	int	length;
	int	index;

	length = utils_strlen(key);
	index = 0;
	while (env[index])
	{
		if (!utils_strncmp(env[index], key, length)
			&& env[index][length] == '=')
		{
			env[index] = utils_strdup(new_value);
			return ;
		}
		index++;
	}
}

void	builtin_cd(t_cmd_line *node)
{
	char	*path;
	char	*buffer[2];

	buffer[0] = smalloc(sizeof(char) * 4096);
	buffer[1] = smalloc(sizeof(char) * 4096);
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
	else
		path = node->next->data;
	getcwd(buffer[0], 4096);
	builtin_cd_run(path);
	getcwd(buffer[1], 4096);
	update_var_for_cd(g_global.g_environments, "PWD",
		utils_strjoin("PWD", "=", buffer[1]));
	update_var_for_cd(g_global.g_environments, "OLDPWD",
		utils_strjoin("OLDPWD", "=", buffer[0]));
}
