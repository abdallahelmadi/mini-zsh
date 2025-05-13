/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:44:11 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_pwd(t_cmd_line *node)
{
	char	*pwd;

	(void)node;
	pwd = smalloc(sizeof(char) * 4096);
	if (pwd == NULL)
		return ;
	getcwd(pwd, 4096);
	printf("%s\n", pwd);
	utils_setexit(SUCCESS);
}
