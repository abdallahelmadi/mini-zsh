/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:51:06 by bnafiai           #+#    #+#             */
/*   Updated: 2025/05/15 18:55:42 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_param(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	builtin_echo(t_cmd_line *node)
{
	t_cmd_line	*temp;
	int			newlinestatus;

	temp = node->next;
	newlinestatus = 1;
	if (temp != NULL && temp->type == TP_STRING
		&& is_param(temp->data))
	{
		newlinestatus = 0;
		temp = temp->next;
	}
	while (temp && temp->type == TP_STRING
		&& utils_strstr_pro(temp->data, "-n"))
		temp = temp->next;
	while (temp != NULL && temp->type == TP_STRING)
	{
		printf("%s", temp->data);
		if (temp->next && temp->next->type == TP_STRING)
			printf(" ");
		temp = temp->next;
	}
	if (newlinestatus)
		printf("\n");
	utils_setexit(SUCCESS);
}
