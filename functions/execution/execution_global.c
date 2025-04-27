/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/26 20:24:09 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	just_directory(char *string)
{
	int	index;
	int	pn;

	index = 0;
	pn = 0;
	while (string[index])
	{
		if (string[index] == '.')
		{
			pn += 1;
			if (pn > 2)
				return (SUCCESS);
			index += 1;
		}
		else if (string[index] == '/')
		{
			index += 1;
			pn = 0;
		}
		else
			return (SUCCESS);
	}
	return (FAILURE);
}

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
	if (!args)
		return ;
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
	dirs = NULL;
	if (path)
		dirs = utils_split(path, ':');
	// Here we will check cmd --------------------------
	if ((node->data)[0] == '.' && (node->data)[1] == '\0')
	{
		printf("minishell: .: filename argument required\n");
		utils_setexit(SYNTAX_ERROR);
	}
	if ((node->data)[0] == '.' && (node->data)[1] == '.' && (node->data)[2] == '\0')
	{
		printf("minishell: ..: Command not found\n");
		utils_setexit(NOT_FOUND);
	}
	if (node->data[0] == '\0')
	{
		printf("minishell: %s: Command not found\n", "");
		utils_setexit(NOT_FOUND);
	}
	if (just_directory(node->data))
	{
		printf("minishell: %s: Is a directory\n", node->data);
		utils_setexit(PERMISSION_DENIED);
	}
	if (access(node->data, F_OK) == 0)
	{
		if (access(node->data, X_OK) == 0)
		{
			execve(node->data, args, g_global.g_environments);
			utils_free(args);
		}
		else
		{
			printf("minishell: %s: Permission denied\n", node->data);
			utils_setexit(PERMISSION_DENIED);
		}
	}
	else
	{
		if (utils_strstr(node->data, "/"))
		{
			printf("minishell: %s: No such file or directory\n", node->data);
			utils_setexit(NOT_FOUND);
		}
		else
		{
			while (dirs && dirs[i])
			{
				full_path = utils_strjoin(dirs[i], "/", node->data);
				if (access(full_path, X_OK) == 0)
					execve(full_path, args, g_global.g_environments);
				free(full_path);
				i++;
			}
		}
		printf("minishell: %s: Command not found\n", node->data);
		utils_setexit(NOT_FOUND);
	}
	// utils_free(args);
	// utils_free(dirs);
	// printf("minishell: %s: Command not found\n", node->data);
	// exit(NOT_FOUND);
}

static void	execution_with_builtin(t_cmd_line *node)
{
	if (utils_strcmp(node->data, "export") == 0)
		builtin_export(node);
	else if (utils_strcmp(node->data, "unset") == 0)
		builtin_unset(node);
	else if (utils_strcmp(node->data, "env") == 0)
		builtin_env(node);
	else if (utils_strcmp(node->data, "pwd") == 0)
		builtin_pwd(node);
	else if (utils_strcmp(node->data, "exit") == 0)
		builtin_exit(node);
	else if (utils_strcmp(node->data, "echo") == 0)
		builtin_echo(node);
	else if (utils_strcmp(node->data, "cd") == 0)
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
		else if (temp->type == TP_REDIR22)
		{
			read_to_delimeter(temp);
			temp = temp->next->next;
		}
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
	int	saved_stdin;
	int saved_stdout;
	t_cmd_line *temp = *node;
	t_cmd_line *temp_check;
	while (temp)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (is_builtin_for_parent(temp) && !has_pipe(temp))
		{
			handle_redirections(temp);
			// if (g_global.g_signal == 1)
			// 	return;
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
				handle_redirections(temp);
				// if (g_global.g_signal == 1)
				// 	exit(SIGNAL_SIGINT);
				temp_check = temp;
				while (temp_check->next)
				{
					if (temp_check->next->type == TP_STRING)
						temp_check = temp_check->next;
					else if (temp_check->next->type == TP_REDIR1 || temp_check->next->type == TP_REDIR11
							|| temp_check->next->type == TP_REDIR2 || temp_check->next->type == TP_REDIR22)
							temp_check = temp_check->next->next;
					else
						break;
				}
				if (temp_check->next && temp_check->next->type == TP_PIPE)
					dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
				execution_with_builtin(temp);
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					utils_setexit(WEXITSTATUS(status));
				// else
				// 	utils_setexit(FAILURE);
				close(fd[1]);
				if (prev_read != 0)
					close(prev_read);
				prev_read = fd[0];
			}
		}
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		while (temp && temp->type != TP_PIPE)
			temp = temp->next;
		if (temp)
			temp = temp->next;
	}
}

void	execution_global(t_cmd_line **cmd_list)
{
	execution_part(cmd_list);
	utils_free_list(cmd_list);
}
