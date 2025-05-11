/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:50:05 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/10 15:52:24 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	just_directory(char *string)
{
	int	index;
	int	pn;

	index = 0;
	pn = 0;
	while (string[index])
	{
		if (string[index] == '.')
		{
			pn += 1;
			if (pn > 2)
				return (SUCCESS);
			index += 1;
		}
		else if (string[index] == '/')
		{
			index += 1;
			pn = 0;
		}
		else
			return (SUCCESS);
	}
	return (FAILURE);
}

void	check_invalid_command(t_cmd_line *node)
{
	if ((node->data)[0] == '.' && (node->data)[1] == '\0')
	{
		printf("minishell: .: filename argument required\n");
		exit(SYNTAX_ERROR);
	}
	if ((node->data)[0] == '.' && (node->data)[1] == '.'
		&& (node->data)[2] == '\0')
	{
		printf("minishell: ..: Command not found\n");
		exit(NOT_FOUND);
	}
	if (node->data[0] == '\0')
	{
		printf("minishell: %s: Command not found\n", "");
		exit(NOT_FOUND);
	}
	if (just_directory(node->data))
	{
		printf("minishell: %s: Is a directory\n", node->data);
		exit(PERMISSION_DENIED);
	}
}
