/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/05 16:06:34 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_env_variable(char *env_name)
{
	int	index;
	char **env;
	index = 0;
	env = g_global.g_environments;
	while (env[index])
	{
		if (utils_strncmp(env[index], env_name, strlen(env_name)) == 0
			&& env[index][strlen(env_name)] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static void	remove_env_var(int token)
{
	int		index;
	int		jndex;
	char	**new_environ;
	char **env;

	index = 0;
	env = g_global.g_environments;
	while (env[index])
		index++;
	new_environ = malloc(sizeof(char *) * index);
	if (new_environ == NULL)
		return ;
	index = 0;
	jndex = 0;
	while (env[index])
	{
		if (index != token)
		{
			new_environ[jndex] = utils_strdup(env[index]);
			jndex++;
		}
		index++;
	}
	new_environ[jndex] = NULL;
	utils_free(env);
	g_global.g_environments = new_environ;
	utils_free(new_environ);
}

void	builtin_unset(t_cmd_line *node)
{
	char		**data;
	char		**env;
	int			index;
	t_cmd_line	*temp;

	temp = node->next;
	while (temp)
	{
		// env = g_global.g_environments;
		// data = utils_split(temp->data, '=');
		// if (data == NULL || data[0] == NULL)
		// 	return (utils_setexit(FAILURE));
		index = find_env_variable(temp->data);
		if (index != -1)
			remove_env_var(index);
		temp = temp->next;
	}
	utils_setexit(SUCCESS);
}
