/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_forbidden_keywords.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:13:36 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/25 10:44:28 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsin_forbidden_keywords(const char *command_line)
{
	if (utils_strstr(command_line, ";"))
	{
		printf("minishell: syntax error, unsupported `;`\n");
		utils_setexit(SYNTAX_ERROR);
		return (free((char *)command_line), FAILURE);
	}
	if (utils_strstr(command_line, ">>>"))
	{
		printf("minishell: syntax error, near unexpected token `>`\n");
		utils_setexit(SYNTAX_ERROR);
		return (free((char *)command_line), FAILURE);
	}
	if (utils_strstr(command_line, "<<<"))
	{
		printf("minishell: syntax error, near unexpected token `<`\n");
		utils_setexit(SYNTAX_ERROR);
		return (free((char *)command_line), FAILURE);
	}
	if (utils_strstr(command_line, "||"))
	{
		printf("minishell: syntax error, near unexpected token `|`\n");
		utils_setexit(SYNTAX_ERROR);
		return (free((char *)command_line), FAILURE);
	}
	return (SUCCESS);
}
