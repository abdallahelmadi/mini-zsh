/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 17:16:14 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv)
{
	char	*command_line;
	char	*command_prompt;

	if (arc == 1 && arv)
	{
		while (1)
		{
			command_prompt = readline_prompt(0);
			command_line = readline(command_prompt);
			printf("=> (%s)\n", command_line);
			free(command_line);
			free(command_prompt);
		}
		return (0);
	}
	printf("\033[31mError\n\033[0m\033[32mRun:\033[0m \033[35m./minishell\n");
	return (1);
}
