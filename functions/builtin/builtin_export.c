/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:49 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/13 17:30:50 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	only_key(t_cmd_line *temp)
{
	if (!check_in(g_global.g_environments, temp->data))
	{
		if (!name_checker(temp->data))
			g_global.g_environments = add_to_environ(g_global.g_environments,
					utils_strjoin(temp->data, "=", ""));
		else
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	checkin_the_loop(t_cmd_line *temp, char ***env)
{
	char	*plus_sign;

	if (temp->data[0] == '=')
		return (printf("minishell: export: `%s`: not a valid identifier\n",
				temp->data), FAILURE);
	if (!utils_strstr(temp->data, "="))
		return (only_key(temp));
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
