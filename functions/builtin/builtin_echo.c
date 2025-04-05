/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:51:06 by bnafiai           #+#    #+#             */
/*   Updated: 2025/04/05 11:11:39 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	builtin_echo_putnbr(int nbr)
{
	char	c;

	if (nbr > 9)
	{
		builtin_echo_putnbr(nbr / 10);
		builtin_echo_putnbr(nbr % 10);
	}
	else
	{
		c = nbr + 48;
		write(1, &c, 1);
	}
}

static void	builtin_echo_putstr(char *string)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] == 2 && string[index + 1] == 2)
		{
			builtin_echo_putnbr(utils_getexit());
			index++;
		}
		else
			write(1, &string[index], 1);
		index++;
	}
}

void	builtin_echo(t_cmd_line *node)
{
	t_cmd_line	*temp;
	int			newlinestatus;

	temp = node->next;
	newlinestatus = 1;
	if (temp != NULL && temp->type == TP_STRING
		&& utils_strcmp(temp->data, "-n") == 0)
	{
		newlinestatus = 0;
		temp = temp->next;
	}
	while (temp != NULL && temp->type == TP_STRING)
	{
		builtin_echo_putstr(temp->data);
		write(1, " ", 1);
		temp = temp->next;
	}
	if (newlinestatus)
		printf("\n");
	utils_setexit(SUCCESS);
}
