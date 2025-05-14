/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:13:58 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/13 17:25:49 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	valid_and_prepare(t_cmd_line *temp, char ***env, char **strtemp)
{
	temp->data = change(temp->data);
	*env = utils_split_pro(temp->data, "+=");
	if (!*env || !(*env)[0] || !(*env)[1])
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				temp->data), 1);
	*strtemp = reset((*env)[1]);
	return (SUCCESS);
}

int	add_and_append(t_cmd_line *temp, char ***env)
{
	char	*strtemp;

	if (valid_and_prepare(temp, env, &strtemp) != 0)
		return (FAILURE);
	if (check_in(g_global.g_environments, (*env)[0]))
	{
		if (!name_checker((*env)[0]))
			append_var(g_global.g_environments, (*env)[0], strtemp);
		else
			return (FAILURE);
	}
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
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	valid_and_prep_update(t_cmd_line *temp, char ***env, char **strtemp)
{
	temp->data = change(temp->data);
	*env = utils_split(temp->data, '=');
	if (!*env || !(*env)[0])
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				temp->data),
			FAILURE);
	if ((*env)[1])
		reset((*env)[1]);
	if ((*env)[1])
		*strtemp = utils_strjoin((*env)[0], "=", (*env)[1]);
	else
		*strtemp = utils_strjoin((*env)[0], "=", "");
	return (SUCCESS);
}

int	add_and_update(t_cmd_line *temp, char ***env)
{
	char	*strtemp;

	if (valid_and_prep_update(temp, env, &strtemp) != 0)
		return (FAILURE);
	if (!check_in(g_global.g_environments, (*env)[0]))
	{
		if (!name_checker((*env)[0]))
		{
			g_global.g_environments = add_to_environ(g_global.g_environments,
					strtemp);
			if (!g_global.g_environments)
				return (FAILURE);
		}
		else
			return (FAILURE);
	}
	else
		update_var(g_global.g_environments, (*env)[0], strtemp);
	return (SUCCESS);
}
