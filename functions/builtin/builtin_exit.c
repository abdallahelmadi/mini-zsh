/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:19:00 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/16 14:08:16 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_numeric(char *string)
{
	int	index;

	index = 0;
	if (string[index] == '-' || string[index] == '+')
		index++;
	while (string[index] >= '0' && string[index] <= '9')
		index++;
	if (string[index] == '\0')
		return (1);
	return (SUCCESS);
}

static void	print_err(char *err)
{
	printf("exit\nminishell: exit: %s: numeric argument required\n",
		err);
	smalloc(-1);
	exit(2);
}

static long	str2nbr(char *string)
{
	int		index;
	int		sign;
	long	result;

	index = 0;
	sign = 1;
	result = 0;
	if (string[index] == '-' || string[index] == '+')
	{
		if (string[index] == '-')
			sign = -1;
		index++;
	}
	while (string[index] >= '0' && string[index] <= '9')
	{
		result = result * 10 + (string[index] - 48);
		if (sign == 1 && ((unsigned long)result > 9223372036854775807UL))
			print_err(string);
		if (sign == -1 && ((unsigned long)result > 9223372036854775808UL))
			print_err(string);
		index++;
	}
	return (result * sign);
}

static int	args_counter(t_cmd_line *node)
{
	int			counter;
	t_cmd_line	*tmp;

	tmp = node->next;
	counter = 0;
	while (tmp && tmp->type == TP_STRING)
	{
		counter++;
		tmp = tmp->next;
	}
	return (counter);
}

void	builtin_exit(t_cmd_line *node)
{
	int	value;

	if (args_counter(node) == 0)
		return (printf("exit\n"), smalloc(-1), exit(utils_getexit()));
	else if (args_counter(node) == 1)
	{
		if (is_numeric(node->next->data))
		{
			value = str2nbr(node->next->data) % 256;
			return (smalloc(-1), printf("exit\n"), exit(value));
		}
		else
			print_err(node->next->data);
	}
	else
	{
		if (is_numeric(node->next->data))
		{
			printf("exit\nbash: exit: too many arguments\n");
			return (smalloc(-1), exit(1));
		}
		else
			print_err(node->next->data);
	}
}
