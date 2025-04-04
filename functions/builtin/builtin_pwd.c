/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 15:02:33 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(t_cmd_line *node)
{
	char *pwd;
	(void)node;
	pwd = malloc(sizeof(char) * 4096);
	if (!pwd)
		return;
	getcwd(pwd, 4096);
	printf("%s\n", pwd);
	free(pwd);
	utils_setexit(SUCCESS);
}
