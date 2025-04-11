/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/11 18:53:29 by bnafiai          ###   ########.fr       */
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
	args = malloc(sizeof(char *) * (count + 2));
	args[0] = node->data;
	tmp = node->next;
	int j = 0;
	while (tmp && tmp->type != TP_PIPE)
	{
		if (tmp->type == TP_STRING)
			args[++j] = tmp->data;
		else if (tmp->type == TP_REDIR1 || tmp->type == TP_REDIR11 || tmp->type == TP_REDIR2)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	args[++j] = NULL;
	path = utils_getenv("PATH");
	dirs = utils_split(path, ':');
	while (dirs[i])
	{
		full_path = utils_strjoin(dirs[i], "/", node->data);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, args, g_global.g_environments);
		}
		free(full_path);
		i++;
	}
	free(path);
	utils_free(args);
	utils_free(dirs);
}

static void	execution_with_builtin(t_cmd_line *node)
{
	if (utils_strstr_pro(node->data, "export"))
		builtin_export(node);
	else if (utils_strstr_pro(node->data, "unset"))
		builtin_unset(node);
	else if (utils_strstr_pro(node->data, "env"))
		builtin_env(node);
	else if (utils_strstr_pro(node->data, "pwd"))
		builtin_pwd(node);
	else if (utils_strstr_pro(node->data, "exit"))
		builtin_exit(node);
	else if (utils_strstr_pro(node->data, "echo"))
		builtin_echo(node);
	else if (utils_strstr_pro(node->data, "cd"))
		builtin_cd(node);
	else
		execution_v(node);
}
int	is_builtin_for_parent(t_cmd_line *node)
{
	if (utils_strstr_pro(node->data, "cd") || utils_strstr_pro(node->data, "export")
		|| utils_strstr_pro(node->data, "unset") || utils_strstr_pro(node->data, "exit"))
		return (1);
	return (0);
}
int	has_pipe(t_cmd_line *node)
{
	t_cmd_line *temp = node;
	while (temp)
	{
		if (temp->type == TP_PIPE)
			return (1);
		temp = temp->next;
	}
	return (0);
}
void	handle_redirections(t_cmd_line *node)
{
	t_cmd_line *temp = node;
	while (temp)
	{
		if (temp->type == TP_REDIR1)
		{
			write_to(temp);
			temp = temp->next->next;
		}
		else if (temp->type == TP_REDIR11)
		{
			write_into(temp);
			temp = temp->next->next;
		}
		else if (temp->type == TP_REDIR2)
		{
			read_from(temp);
			temp = temp->next->next;
		}
		// else if (temp->type == TP_REDIR22)
		// {
		// 	read_to_delimeter(temp);
		// 	tmp = temp->next->next;
		// }
		else
			temp = temp->next;
	}
}
void	execution_part(t_cmd_line **node)
{
	int	fd[2];
	int	prev_read = 0;
	pid_t	pid;
	int	status;
	t_cmd_line *temp = *node;
	t_cmd_line *temp_check;
	while (temp)
	{
		if (is_builtin_for_parent(temp) && !has_pipe(temp))
		{
			handle_redirections(temp);
			execution_with_builtin(temp);
		}
		else
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
				temp_check = temp;
				while (temp_check->next && temp_check->next->type == TP_STRING)
					temp_check = temp_check->next;
				if (temp_check->next && temp_check->next->type == TP_PIPE)
					dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				handle_redirections(temp);
				execution_with_builtin(temp);
				exit(SUCCESS);
			}
			else
			{
				waitpid(pid , &status, 0);
				close(fd[1]);
				if (prev_read != 0)
					close(prev_read);
				prev_read = fd[0];
			}
		}
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
}

void	execution_global(t_cmd_line **cmd_list)
{
	if (execution_syntax(cmd_list))
		return ;
	execution_part(cmd_list);
	utils_free_list(cmd_list);
}
