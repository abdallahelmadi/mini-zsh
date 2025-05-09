/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:49 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/09 15:37:27 by bnafiai          ###   ########.fr       */
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
			env[index] = new_value;
			return ;
		}
		index++;
	}
}

static void	append_var(char **env, char *key, char *new_value)
{
	int	length;
	int	index;

	length = strlen(key);
	index = 0;
	while (env[index])
	{
		if (!utils_strncmp(env[index], key, length) && env[index][length] == '=')
		{
			char *temp = utils_strdup(env[index]);
			env[index] = utils_strjoin(temp, new_value, "");
			return ;
		}
		index++;
	}
}

static char	*change(char *str)
{
	int i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		if (str[i] == '=')
			str[i] = 1;
		i++;
	}
	return (str);
}

static char *reset(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = '=';
		i++;
	}
	return str;
}
int	check_str(char *str)
{
	if (str[0] == '=')
	{
		printf("minishell : %s : not a valid identifier\n", str);
		return (1);
	}
	return (0);
}
int	name_checker(char *str)
{
	int i = 0;
	if (!str || str[0] == '\0')
	{
		printf("minishell : %s : not a valid identifier\n", str);
		return (1);
	}
	if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] == '_')))
	{
		printf("minishell : %s : not a valid identifier\n", str);
		return (1);
	}
	i++;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] == '_') || (str[i] >= '0' && str[i] <= '9')))
		{
			printf("minishell : %s : not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return 0;
}
static int	add_and_append(t_cmd_line *temp, char ***env)
{
	char	*strtemp;

	temp->data = change(temp->data);
	*env = utils_split_pro(temp->data, "+=");
	if (!*env || !(*env)[0] || !(*env)[1])
	{
		printf("minishell: export: `%s`: not a valid identifier\n", temp->data);
		return (FAILURE);
	}
	strtemp = reset((*env)[1]);
	if (check_in(g_global.g_environments, (*env)[0]) && !name_checker((*env)[0]))
		append_var(g_global.g_environments, (*env)[0], strtemp);
	else
	{
		if (!name_checker((*env)[0]))
		{
			strtemp = utils_strjoin((*env)[0], "=", (*env)[1]);
			g_global.g_environments = add_to_environ(g_global.g_environments,
				strtemp);
			if (!g_global.g_environments)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
static int	add_and_update(t_cmd_line *temp, char ***env)
{
	char	*strtemp;

	temp->data = change(temp->data);
	*env = utils_split(temp->data, '=');
	if (!*env || !(*env)[0])
	{
		printf("minishell: export: `%s`: not a valid identifier\n", temp->data);
		return (FAILURE);
	}
	if ((*env)[1])
		reset((*env)[1]);
	if ((*env)[1])
		strtemp = utils_strjoin((*env)[0], "=", (*env)[1]);
	else
		strtemp = utils_strjoin((*env)[0], "=", "");
	if (!check_in(g_global.g_environments, (*env)[0]) && !name_checker((*env)[0]))
	{
		g_global.g_environments = add_to_environ(g_global.g_environments,
				strtemp);
		if (!g_global.g_environments)
			return (FAILURE);
	}
	else
		update_var(g_global.g_environments, (*env)[0], strtemp);
	return (SUCCESS);
}
static int	checkin_the_loop(t_cmd_line *temp, char ***env)
{
	char	*plus_sign;

	if (temp->data[0] == '=')
	{
		printf("minishell: export: `%s`: not a valid identifier\n", temp->data);
		return (FAILURE);
	}
	if (!utils_strstr(temp->data, "="))
	{
		if (!check_in(g_global.g_environments, temp->data) && !name_checker(temp->data))
			g_global.g_environments = add_to_environ(g_global.g_environments,
					utils_strjoin(temp->data, "=", ""));
	}
	else
	{
		if (check_str(temp->data) == 1)
			return (1);
		plus_sign = utils_strstr(temp->data, "+=");
		if (plus_sign)
			add_and_append(temp, env);
		else
			add_and_update(temp, env);
	}
	return (SUCCESS);
}
void	printed_export(char	**env)
{
	char	**split;

	while (*env)
	{
		split = utils_split((*env), '=');
		if (split[1])
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		else
			printf("declare -x %s\n", split[0]);
		env++;
	}
	return ;
}
void	builtin_export(t_cmd_line *node)
{
	char		**env;
	t_cmd_line	*temp;
	int			exit_check;

	exit_check = 0;
	if (node->next == NULL || node->next->type != TP_STRING)
	{
		env = g_global.g_environments;
		printed_export(env);
	}
	temp = node->next;
	while (temp && temp->type == TP_STRING)
	{
		if (checkin_the_loop(temp, &env) == 1)
			exit_check = 1;
		temp = temp->next;
	}
	utils_setexit(exit_check);
}
