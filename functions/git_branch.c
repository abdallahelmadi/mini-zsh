/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:40:12 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 02:47:02 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*git_branch(void)
{
	pid_t	child;
	ssize_t	readed;
	int		pipefds[2];
	char	buffer[2048];
	char	**gitcmd;

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
	{
		close(pipefds[0]);
		dup2(pipefds[1], 1);
		close(pipefds[1]);
		// split the command line : 'git branch' and give it to execve
		if (execve(gitcmd[0], gitcmd, NULL) == -1)
			return (NULL);
	}
	else
	{
		// waitpid(child, NULL, 0);
		// close(pipefds[1]);
		// dup2(pipefds[0], 0);
		// close(pipefds[0]);
		// buffer = malloc(sizeof(char) * 2);
		// buffer[1] = '\0';
		// if (buffer == NULL)
		// 	return (NULL);
		// while (1)
		// {
		// 	readed = read(0, buffer, 1);
		// 	if (readed == 0 || readed == -1)
		// 		break ;
		// 	printf("%s", buffer);
		// }
		// free(buffer);
	}
	return (NULL);
}
