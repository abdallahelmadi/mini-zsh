/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/08 19:26:40 by bnafiai          ###   ########.fr       */
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
static void	execution_v(t_cmd_line *node)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	char	**args;
	int i = 0;
	int count = 0;
	t_cmd_line *tmp = node->next;
	while (tmp && tmp->type == TP_STRING)
	{
		count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	tmp = node;
	int j = 0;
	while (tmp && tmp->type != TP_PIPE)
	{
		args[j] = tmp->data;
		j++;
		tmp = tmp->next;
	}
	args[j] = NULL;
	path = utils_getenv("PATH");
	dirs = utils_split(path, ':');
	while (dirs[i])
	{
		full_path = utils_strjoin(dirs[i], "/", node->data);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, args, g_global.g_environments);
		}
		i++;
	}
	// utils_free(dirs);
}
void	execution_part(t_cmd_line **node)
{
	int	fd[2];
	int	prev_read = 0;
	pid_t	pid;
	// int	status;
	t_cmd_line *temp = *node;
	t_cmd_line *testtt;
	while (temp)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_read != 0)
			{
				dup2(prev_read, 0);
				close(prev_read);
			}
			testtt = temp;
			while (testtt->next && testtt->next->type == TP_STRING)
				testtt = testtt->next;
			if (testtt->next && testtt->next->type == TP_PIPE)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execution_v(temp);
		}
		else
		{
			waitpid(pid ,NULL, 0);
			close(fd[1]);
			if (prev_read != 0)
				close(prev_read);
			prev_read = fd[0];
		}
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
}
// static void	is_builtin(t_cmd_line *node)
// {
// 	t_cmd_line *x = node;
// 	if (x->type == 0 && utils_strstr_pro(x->data, "export"))
// 		builtin_export(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "unset"))
// 		builtin_unset(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "env"))
// 		builtin_env(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "pwd"))
// 		builtin_pwd(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "exit"))
// 		builtin_exit(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "echo"))
// 		builtin_echo(x);
// 	else if (x->type == 0 && utils_strstr_pro(x->data, "cd"))
// 		builtin_cd(x);
// }
void	execution_global(t_cmd_line **cmd_list)
{
	if (execution_syntax(cmd_list))
		return ;
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
	// else
	execution_part(cmd_list);
	// is_builtin(*cmd_list);
	utils_free_list(cmd_list);
}
