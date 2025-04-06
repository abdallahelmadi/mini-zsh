/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:25:23 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/05 15:47:07 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**utils_gsetenv(const char **env)
{
	char	**new_env;
	int		index;

	index = 0;
	if (env == NULL)
		return (g_global.g_environments);
	else
	{
		while (env[index] != NULL)
			index++;
		new_env = (char **)malloc(sizeof(char *) * (index + 1));
		if (new_env == NULL)
			return (NULL);
		index = 0;
		while (env[index] != NULL)
		{
			new_env[index] = utils_strdup(env[index]);
			index++;
		}
		new_env[index] = NULL;
		return (new_env);
	}
}
