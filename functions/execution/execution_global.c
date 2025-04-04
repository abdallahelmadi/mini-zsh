/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:39:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 18:09:14 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execution_global(t_cmd_line **cmd_list)
{
	if (execution_syntax(cmd_list))
		return ;

	t_cmd_line *x = *cmd_list;
	// while (x)
	// {
		if (x->type == 0 && utils_strstr_pro(x->data, "export"))
			builtin_export(*cmd_list);
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
	// 	x = x->next;
	// 	while (x != NULL && x->type == 2)
	// 		x = x->next;
	// }

	utils_free_list(cmd_list);
}
