/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:05:59 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/13 16:36:59 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*change(char *str)
{
	int	i;

	i = 0;
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

char	*reset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = '=';
		i++;
	}
	return (str);
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
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (printf("minishell : %s : not a valid identifier\n", str), 1);
	if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] == '_')))
		return (printf("minishell : %s : not a valid identifier\n", str), 1);
	i++;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] == '_')
				|| (str[i] >= '0' && str[i] <= '9')))
		{
			return (printf("minishell : %s : not a valid identifier\n", str),
				1);
		}
		i++;
	}
	return (0);
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
