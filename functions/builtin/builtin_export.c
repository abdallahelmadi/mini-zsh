/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:49 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/09 15:42:34 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_in(char **env, char *str)
{
	int	index;
	int	length;

	index = 0;
	length = utils_strlen(str);
	while (env[index] != NULL)
	{
		if (!utils_strncmp(env[index], str, length)
			&& env[index][length] == '=')
			return (1);
		index++;
	}
	return (0);
}

static char	**add_to_environ(char **environ, char *new_var)
{
	int		index;
	int		jndex;
	char	**new_environ;

	index = 0;
	while (environ[index])
		index++;
	new_environ = malloc(sizeof(char *) * (index + 2));
	if (!new_environ)
		return (NULL);
	jndex = 0;
	while (jndex < index)
	{
		new_environ[jndex] = utils_strdup(environ[jndex]);
		jndex++;
	}
	new_environ[index] = new_var;
	new_environ[index + 1] = NULL;
	utils_free(environ);
	return (new_environ);
}

static void	update_var(char **env, char *key, char *new_value)
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
			free(env[index]);
			env[index] = new_value;
			return ;
		}
		index++;
	}
}

static void	checkin_the_loop(t_cmd_line *temp, char **strtemp, char ***env)
{
	if (!utils_strstr(temp->data, "="))
	{
		if (!check_in(g_global.g_environments, temp->data))
			g_global.g_environments = add_to_environ(g_global.g_environments,
					utils_strjoin(temp->data, "=", ""));
	}
	else
	{
		*env = utils_split(temp->data, '=');
		*strtemp = utils_strjoin((*env)[0], "=", (*env)[1]);
		if (!check_in(g_global.g_environments, (*env)[0]))
		{
			g_global.g_environments = add_to_environ(g_global.g_environments,
					*strtemp);
			if (!g_global.g_environments)
			{
				free(*strtemp);
				utils_free(*env);
				return ;
			}
		}
		else
			update_var(g_global.g_environments, (*env)[0], *strtemp);
		utils_free((*env));
	}
}

void	builtin_export(t_cmd_line *node)
{
	char		**env;
	char		*strtemp;
	t_cmd_line	*temp;

	strtemp = NULL;
	if (node->next == NULL || node->next->type != TP_STRING)
	{
		env = g_global.g_environments;
		while (*env)
		{
			strtemp = utils_strjoin("declare -x", " ", *env);
			printf("%s\n", strtemp);
			free(strtemp);
			env++;
		}
		return ;
	}
	temp = node->next;
	while (temp && temp->type == TP_STRING)
	{
		checkin_the_loop(temp, &strtemp, &env);
		temp = temp->next;
	}
	utils_setexit(SUCCESS);
}
