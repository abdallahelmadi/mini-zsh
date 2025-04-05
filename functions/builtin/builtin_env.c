/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/05 11:36:05 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		printf("%s\n", env[index]);
		index++;
	}
	utils_setexit(SUCCESS);
}
