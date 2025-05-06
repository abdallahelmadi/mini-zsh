/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:42:14 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_env(char *str)
{
	char	**split;

	split = utils_split(str, '=');
	if (split[1])
		return (0);
	else
		return (1);
}

void	builtin_env(t_cmd_line *node)
{
	char	**env;
	int		index;

	if (node->next && node->next->type == TP_STRING)
	{
		if (access(node->next->data, F_OK) == 0)
			return (printf("minishell: env: %s: Permission denied\n",
					node->next->data), utils_setexit(PERMISSION_DENIED));
		else
			return (printf("minishell: env: %s: No such file or directory\n",
					node->next->data), utils_setexit(NOT_FOUND));
	}
	index = 0;
	env = utils_gsetenv(NULL);
	while (env[index])
	{
		if (!check_env(env[index]))
			printf("%s\n", env[index]);
		index++;
	}
	utils_setexit(SUCCESS);
}
