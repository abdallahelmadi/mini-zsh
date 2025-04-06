/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:49 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/05 15:43:24 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// extern char **environ;

void	free_array(char **str)
{
	int i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
//check wach kayn variable f env
static int check_in(char **env, char *str)
{
	int i = 0;
	int len = utils_strlen(str);
	while (env[i])
	{
		if (!utils_strncmp(env[i], str, len) && env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}
// zid variable jdid ila makanch f env
static char **add_to_environ(char **environ, char *new_var)
{
	int i = 0;
	int j;
	char **new_environ;

	while (environ[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_environ[j] = utils_strdup(environ[j]);
		j++;
	}
	new_environ[i] = utils_strdup(new_var);
	new_environ[i + 1] = NULL;
	free(environ);
	return (new_environ);
}
static void update_var(char **env, char *key, char *new_value)
{
	int len = utils_strlen(key);
	int i = 0;
	while (env[i])
	{
		if (!utils_strncmp(env[i], key, len) && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = new_value;
			return ;
		}
		i++;
	}
}
void builtin_export(t_cmd_line *node)
{
	char **env;
	char *joined;
	t_cmd_line *tmp;

	if (!node->next)
	{
		env = g_global.g_environments;
		while (*env)
		{
			joined = utils_strjoin("declare -x", " ", *env);
			if (joined)
			{
				printf("%s\n", joined);
				free(joined);
			}
			env++;
		}
	}
	else
	{
		tmp = node->next;
		while (tmp)
		{
			if (!utils_strstr(tmp->data, "="))
			{
				if (!check_in(g_global.g_environments, tmp->data))
				{
					joined = utils_strjoin(tmp->data, "=", "");
					g_global.g_environments = add_to_environ(g_global.g_environments, joined);
				}
			}
			else
			{
				env = utils_split(tmp->data, '=');
				joined = utils_strjoin(env[0], "=", env[1]);
				if (!joined)
				{
					free_array(env);
					return ;
				}
				if (!check_in(g_global.g_environments, env[0]))
				{
					g_global.g_environments = add_to_environ(g_global.g_environments, joined);
					if (!g_global.g_environments)
					{
						free(joined);
						free_array(env);
						return ;
					}
				}
				else
					update_var(g_global.g_environments, env[0], joined);
				free_array(env);
			}
		tmp = tmp->next;
		}
	}
	utils_setexit(SUCCESS);
}
