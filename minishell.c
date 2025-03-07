/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 14:50:18 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv)
{
	int		command_status;
	char	*readlineprompt;

	command_status = 0;
	if (arc == 1 && arv)
	{
		while (1)
		{
			readlineprompt = readline_prompt(command_status);
			readline(readlineprompt);
			free(readlineprompt);
		}
		return (0);
	}
	printf("\033[31mError\n\033[0m\033[32mRun:\033[0m \033[35m./minishell\n");
	return (1);
}
