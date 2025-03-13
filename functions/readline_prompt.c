/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:18:51 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/13 15:01:32 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*readline_prompt(void)
{
	char	*laststatus;
	char	*foldername;
	char	*gitbranch;
	char	*result;
	char	*temp;

	if (g_lastexitstatus == 0)
		laststatus = "\033[32m";
	else
		laststatus = "\033[31m";
	foldername = get_folder_name();
	gitbranch = git_branch();
	temp = utils_strjoin(laststatus, "➜  \033[0m", "\033[1;36m");
	result = utils_strjoin(temp, foldername, "\033[0m ");
	free(temp);
	free(foldername);
	if (gitbranch == NULL)
		return (result);
	temp = utils_strjoin(result, "\033[1;34mgit:(\033[0m", "\033[1;31m");
	free(result);
	result = utils_strjoin(temp, gitbranch,
			"\033[0m\033[1;34m)\033[0m \033[1;33m✗\033[0m ");
	free(temp);
	free(gitbranch);
	return (result);
}
