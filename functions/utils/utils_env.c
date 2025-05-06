/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:25:23 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:09:45 by abdael-m         ###   ########.fr       */
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
		new_env = (char **)smalloc(sizeof(char *) * (index + 1));
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
