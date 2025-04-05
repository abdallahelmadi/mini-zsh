/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/05 11:45:32 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(t_cmd_line *node)
{
	char	*pwd;

	(void)node;
	pwd = malloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return ;
	getcwd(pwd, 4096);
	printf("%s\n", pwd);
	free(pwd);
	utils_setexit(SUCCESS);
}
