/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:20:24 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/10 15:29:10 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_in(char **env, char *str)
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

char	**add_to_environ(char **environ, char *new_var)
{
	int		index;
	int		jndex;
	char	**new_environ;

	index = 0;
	while (environ[index])
		index++;
	new_environ = smalloc(sizeof(char *) * (index + 2));
	jndex = 0;
	while (jndex < index)
	{
		new_environ[jndex] = utils_strdup(environ[jndex]);
		jndex++;
	}
	new_environ[index] = new_var;
	new_environ[index + 1] = NULL;
	return (new_environ);
}

void	update_var(char **env, char *key, char *new_value)
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
			env[index] = new_value;
			return ;
		}
		index++;
	}
}

void	append_var(char **env, char *key, char *new_value)
{
	int		length;
	int		index;
	char	*temp;

	length = strlen(key);
	index = 0;
	while (env[index])
	{
		if (!utils_strncmp(env[index], key, length)
			&& env[index][length] == '=')
		{
			temp = utils_strdup(env[index]);
			env[index] = utils_strjoin(temp, new_value, "");
			return ;
		}
		index++;
	}
}
