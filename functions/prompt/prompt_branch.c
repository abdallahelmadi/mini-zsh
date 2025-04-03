/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:40:12 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/03 18:16:55 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_child(int *pipefds)
{
	char	**gitcmd;

	close(pipefds[0]);
	dup2(pipefds[1], 1);
	dup2(pipefds[1], 2);
	close(pipefds[1]);
	gitcmd = utils_split("/usr/bin/git branch --show-current", ' ');
	execve(gitcmd[0], gitcmd, NULL);
}

static char	*ft_parent(int *pipefds, int child)
{
	int		readed;
	char	*buffer;

	waitpid(child, NULL, 0);
	close(pipefds[1]);
	buffer = malloc(sizeof(char) * 100);
	if (buffer == NULL)
		return (NULL);
	readed = read(pipefds[0], buffer, 99);
	close(pipefds[0]);
	buffer[readed] = '\0';
	if (utils_charcmp(buffer, ' ') == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer[readed - 1] = '\0';
	return (buffer);
}

char	*prompt_branch(void)
{
	pid_t	child;
	int		pipefds[2];

	if (pipe(pipefds) == -1)
		return (NULL);
	child = fork();
	if (child == -1)
	{
		close(pipefds[0]);
		close(pipefds[1]);
		return (NULL);
	}
	if (child == 0)
		ft_child(pipefds);
	return (ft_parent(pipefds, child));
}
