// int	read_file;

// 	command = command_line(av[2], env);
// 	if (command == NULL)
// 		exit (-1);
// 	read_file = open(av[1], O_RDONLY);
// 	if (read_file == -1)
// 	{
// 		px_free(command);
// 		if (access(av[1], F_OK))
// 			exit (px_printf(2, 2, "%s: No such file or directory\n", av[1]));
// 		exit (px_printf(2, 2, "%s: Permission denied\n", av[4]));
// 	}
// 	dup2(read_file, 0);
// 	dup2(pipe_fd[1], 1);
// 	close(read_file);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	if (execve(command[0], command, NULL) == -1)
// 		exit (px_printf(2, 2, "Error\nCannot run command !\n"));


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:12:23 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/02 07:34:25 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	**command_line_other_continue(char *temp, int index,
	char **path, char **command)
{
	char	*other_temp;

	temp = px_strjoin(path[index], "/");
	other_temp = px_strjoin(temp, command[0]);
	free(temp);
	if (access(other_temp, X_OK) == 0)
	{
		free(command[0]);
		command[0] = other_temp;
		return (px_free(path), command);
	}
	free(other_temp);
	return (NULL);
}

static char	**command_line_continue(char **command, char **env)
{
	char	**path;
	char	*temp;
	int		index;

	if (is_command(command[0]))
	{
		temp = px_strncmp((const char **)env, "PATH=", 5);
		if (temp == NULL)
			return (px_free(command), NULL);
		path = px_split(temp, ':');
		free(temp);
		index = 0;
		while (path[index] != NULL)
		{
			if (command_line_other_continue(temp, index, path, command))
				return (command);
			index++;
		}
		return (px_printf(-1, 2, "%s: Command not found\n", command[0]),
			px_free(command), px_free(path), NULL);
	}
	return (px_printf(-1, 2, "%s: No such file or directory\n", command[0]),
		px_free(command), NULL);
}

char	**command_line(const char *string, char **env)
{
	char	**command;

	if (empty_arg((char *)string) == 1)
		return (px_printf(-1, 2, " : Command not found\n"), NULL);
	command = px_split(string, ' ');
	if (command == NULL)
		return (NULL);
	if (command[0][0] == '.' && command[0][1] == '\0')
		return (px_printf(-1, 2, ".: filename argument required\n"),
			px_free(command), NULL);
	if (is_empty_path(command[0]))
	{
		if (is_empty_path(command[0]) == 2)
			return (px_printf(-1, 2, "%s: Is a directory\n", command[0]),
				px_free(command), NULL);
		return (px_printf(-1, 2, "%s: Command not found\n", command[0]),
			px_free(command), NULL);
	}
	if (access(command[0], X_OK) == 0)
		return (command);
	if (access(command[0], F_OK) == 0 && !is_command(command[0]))
		return (px_printf(-1, 2, "%s: Permission denied\n", command[0]),
			px_free(command), NULL);
	return (command_line_continue(command, env));
}
