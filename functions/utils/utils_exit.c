/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:54:20 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/22 16:32:44 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	utils_setexit(int status)
{
	g_global.g_oldlastexitstatus = g_global.g_lastexitstatus;
	g_global.g_lastexitstatus = status;
}

int	utils_getexit(void)
{
	return (g_global.g_oldlastexitstatus);
}
