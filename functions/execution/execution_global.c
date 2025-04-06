/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/06 19:26:02 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ---------------------------------------------------------------------
// t_cmd_line *x = *cmd_list;
// if (x->type == 0 && utils_strstr_pro(x->data, "export"))
// 	builtin_export(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "unset"))
// 	builtin_unset(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "env"))
// 	builtin_env(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "pwd"))
// 	builtin_pwd(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "exit"))
// 	builtin_exit(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "echo"))
// 	builtin_echo(x);
// else if (x->type == 0 && utils_strstr_pro(x->data, "cd"))
// 	builtin_cd(x);
// ---------------------------------------------------------------------
void	execution_v(t_cmd_line *node)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	char	**args;
	int i = 0;
	int count = 0;
	t_cmd_line *tmp = node;
	while (tmp && tmp->type != TP_PIPE)
	{
		count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 2));
	tmp = node;
	int j = 0;
	while (tmp && tmp->type != TP_PIPE)
	{
		args[j] = tmp->data;
		j++;
		tmp = tmp->next;
	}
	args[j] = NULL;
	path = getenv("PATH");
	dirs = utils_split(path, ':');
	while (dirs[i])
	{
		full_path = utils_strjoin(dirs[i], "/", node->data);
		if (access(full_path, X_OK) == 0)
		{
			break;
		}
		i++;
	}
	if (!dirs[i])
		perror("Command not exist");
	else
		execv(full_path, args);
}
void	execution_part(t_cmd_line **node)
{
	int	fd[2];
	pid_t	pid;
	int	status;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execution_v(*node);
	}
	else
	{
		close(fd[1]);
		char	buffer[1024];
		int		readed;
		readed = read(fd[0], buffer, sizeof(buffer) - 1);
		buffer[readed] = '\0';
		printf("child execution : %s", buffer);
		close(fd[0]);
		waitpid(pid, &status, 0);
	}
}
void	execution_global(t_cmd_line **cmd_list)
{
	if (execution_syntax(cmd_list))
		return ;
	t_cmd_line *x = *cmd_list;
	if (x->type == 0 && utils_strstr_pro(x->data, "export"))
		builtin_export(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "unset"))
		builtin_unset(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "env"))
		builtin_env(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "pwd"))
		builtin_pwd(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "exit"))
		builtin_exit(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "echo"))
		builtin_echo(x);
	else if (x->type == 0 && utils_strstr_pro(x->data, "cd"))
		builtin_cd(x);
	else
		execution_part(cmd_list);
	utils_free_list(cmd_list);
}
