/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:49 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/10 15:40:57 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if (check_in(g_global.g_environments, (*env)[0])
			&& !name_checker((*env)[0]))
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
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				temp->data),
			FAILURE);
	if ((*env)[1])
		reset((*env)[1]);
	if ((*env)[1])
		strtemp = utils_strjoin((*env)[0], "=", (*env)[1]);
	else
		strtemp = utils_strjoin((*env)[0], "=", "");
	if (!check_in(g_global.g_environments, (*env)[0])
		&& !name_checker((*env)[0]))
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
		if (!check_in(g_global.g_environments, temp->data)
			&& !name_checker(temp->data))
			g_global.g_environments = add_to_environ(g_global.g_environments,
					utils_strjoin(temp->data, "=", ""));
	}
	else
	{
		if (check_str(temp->data) == 1)
			return (1);
		plus_sign = utils_strstr(temp->data, "+=");
		if (plus_sign)
			return (add_and_append(temp, env));
		else
			return (add_and_update(temp, env));
	}
	return (SUCCESS);
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
