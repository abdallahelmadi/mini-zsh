/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/08 17:45:06 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execution_global(t_cmd_line **cmd_list)
{
	if (execution_syntax(cmd_list))
		return ;

	// t_cmd_line *curr = *cmd_list;
	// int		prev_read = 0;
	// int		fds[2];
	// pid_t	pid;

	// while (curr)
	// {
	// 	pipe(fds);
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		// Input from previous pipe
	// 		if (prev_read != 0)
	// 		{
	// 			dup2(prev_read, 0);
	// 			close(prev_read);
	// 		}
	// 		// Output to current pipe (only if another command follows)
	// 		if (curr->next && curr->next->type == TP_PIPE)
	// 		{
	// 			dup2(fds[1], 1);
	// 		}
	// 		close(fds[0]);
	// 		close(fds[1]);

	// 		// Collect args
	// 		t_cmd_line *tmp = curr;
	// 		int count = 0;
	// 		while (tmp && tmp->type != TP_PIPE)
	// 		{
	// 			count++;
	// 			tmp = tmp->next;
	// 		}

	// 		char **args = malloc(sizeof(char *) * (count + 1));
	// 		tmp = curr;
	// 		for (int i = 0; i < count; i++)
	// 		{
	// 			args[i] = tmp->data;
	// 			tmp = tmp->next;
	// 		}
	// 		args[count] = NULL;

	// 		char *full_path = utils_strjoin("/usr/bin/", curr->data, "");
	// 		execve(full_path, args, NULL);
	// 		perror("execve");
	// 		free(full_path);
	// 		free(args);
	// 		exit(1);
	// 	}
	// 	else
	// 	{
	// 		wait(NULL);
	// 		close(fds[1]);
	// 		if (prev_read != 0)
	// 			close(prev_read);
	// 		prev_read = fds[0];
	// 	}
	// 	// Skip to next command after pipe
	// 	while (curr && curr->type != TP_PIPE)
	// 		curr = curr->next;
	// 	if (curr)
	// 		curr = curr->next;
	// }
	utils_free_list(cmd_list);
}
