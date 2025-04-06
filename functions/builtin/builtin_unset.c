/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/06 10:31:20 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	find_env_variable(char *env_name, char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (utils_strncmp(env[index], env_name, strlen(env_name)) == 0
			&& env[index][strlen(env_name)] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static void	remove_env_var(int token, char **env)
{
	int		index;
	int		jndex;
	char	**new_environ;

	index = 0;
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
	utils_free(g_global.g_environments);
	g_global.g_environments = new_environ;
}

void	builtin_unset(t_cmd_line *node)
{
	char		**data;
	char		**env;
	int			index;
	t_cmd_line	*temp;

	temp = node->next;
	while (temp && temp->type == TP_STRING)
	{
		env = g_global.g_environments;
		data = utils_split(temp->data, '=');
		if (data == NULL || data[0] == NULL)
			return (utils_setexit(FAILURE));
		index = find_env_variable(data[0], env);
		if (index != -1)
			remove_env_var(index, env);
		utils_free(data);
		temp = temp->next;
	}
	utils_setexit(SUCCESS);
}
