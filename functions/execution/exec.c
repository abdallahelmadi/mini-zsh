/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:21:25 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/12 19:32:25 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_args(t_cmd_line *node)
{
	int			count;
	t_cmd_line	*tmp;

	count = 0;
	tmp = node->next;
	while (tmp && tmp->type != TP_PIPE)
	{
		if (tmp->type == TP_STRING)
			count++;
		else if ((tmp->type == TP_REDIR1 || tmp->type == TP_REDIR11
				|| tmp->type == TP_REDIR2 || tmp->type == TP_REDIR22)
			&& tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}

static char	**allocated_args(t_cmd_line *node, int length)
{
	char		**args;
	t_cmd_line	*tmp;
	int			j;

	args = smalloc(sizeof(char *) * (length + 2));
	if (!args)
		return (NULL);
	args[0] = node->data;
	tmp = node->next;
	j = 1;
	while (tmp && tmp->type != TP_PIPE)
	{
		if (tmp->type == TP_STRING)
			args[j++] = tmp->data;
		else if ((tmp->type == TP_REDIR1 || tmp->type == TP_REDIR11
				|| tmp->type == TP_REDIR2 || tmp->type == TP_REDIR22)
			&& tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	args[j] = NULL;
	return (args);
}

static void	check_access_exec(char **args, t_cmd_line *node)
{
	if (access(node->data, F_OK) == 0 && utils_strstr(node->data, "/"))
	{
		if (access(node->data, X_OK) == 0)
			execve(node->data, args, g_global.g_environments);
		else
		{
			printf("minishell: %s: Permission denied\n", node->data);
			exit(PERMISSION_DENIED);
		}
	}
}

static void	search_and_exec(char **dirs, char **args, t_cmd_line *node)
{
	int		i;
	char	*full_path;

	i = 0;
	if (utils_strstr(node->data, "/"))
	{
		printf("minishell: %s: No such file or directory\n", node->data);
		exit(NOT_FOUND);
	}
	else
	{
		while (dirs && dirs[i])
		{
			full_path = utils_strjoin(dirs[i], "/", node->data);
			if (access(full_path, X_OK) == 0)
				execve(full_path, args, g_global.g_environments);
			i++;
		}
	}
	printf("minishell: %s: Command not found\n", node->data);
	exit(NOT_FOUND);
}

void	execution_v(t_cmd_line *node)
{
	char	*path;
	char	**dirs;
	char	**args;
	int		count;

	count = count_args(node);
	args = allocated_args(node, count);
	dirs = NULL;
	path = utils_getenv("PATH");
	if (path)
		dirs = utils_split(path, ':');
	check_invalid_command(node);
	check_access_exec(args, node);
	search_and_exec(dirs, args, node);
}
