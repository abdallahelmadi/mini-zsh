/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:40:47 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/12 14:51:06 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*utils_getenv(const char *name)
{
	char	**env;
	int		index;

	env = utils_gsetenv(NULL);
	index = 0;
	while (env[index] != NULL)
	{
		if (utils_strstr_pro(env[index], name)
			&& utils_strstr_pro(env[index], name)[utils_strlen(name)] == '=')
			return (utils_strdup(&(env[index][utils_strlen(name) + 1])));
		index++;
	}
	return (NULL);
}
