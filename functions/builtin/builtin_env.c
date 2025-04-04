/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 15:32:38 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern char **environ;

void	builtin_env(t_cmd_line *node)
{
	char **env;
	int	i;
	if (node->next && node->next->type == TP_STRING)
	{
		printf("minishell: env: '%s': No such file or directory\n", node->next->data);
		utils_setexit(NOT_FOUND);
		return ;
	}

	i = 0;
	env = environ;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	utils_setexit(SUCCESS);
}
