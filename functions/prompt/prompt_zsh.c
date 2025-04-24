/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_zsh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:18:51 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/24 11:40:56 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*prompt_zsh(void)
{
	char	*laststatus;
	char	*foldername;
	char	*gitbranch;
	char	*result;
	char	*temp;

	laststatus = "\001\033[32m\002";
	if (g_global.g_lastexitstatus != 0)
		laststatus = "\001\033[31m\002";
	foldername = prompt_folder();
	gitbranch = prompt_branch();
	temp = utils_strjoin(laststatus, "➜  \001\033[0m\002",
			"\001\033[1;36m\002");
	result = utils_strjoin(temp, foldername, "\001\033[0m\002 ");
	free(temp);
	free(foldername);
	if (gitbranch == NULL)
		return (result);
	temp = utils_strjoin(result, "\001\033[1;34m\002git:(\001\033[0m\002",
			"\001\033[1;31m\002");
	free(result);
	foldername = utils_strjoin("\001\033[0m\002\001\033[1;34m\002)",
			"\001\033[0m\002 \001\033[1;33m\002✗\001\033[0m\002 ", "");
	result = utils_strjoin(temp, gitbranch, foldername);
	return (free(temp), free(gitbranch), free(foldername), result);
}
