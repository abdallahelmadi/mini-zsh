/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:56:10 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/12 14:48:47 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	inside_single_quotes(char *string)
{
	int	counter;
	int	index;

	index = 0;
	counter = 0;
	while (string[index])
	{
		if (string[index] == '\'')
			counter++;
		index++;
	}
	if (counter == 1 || counter % 2 == 1)
		return (FAILURE);
	return (SUCCESS);
}

static int	condition_num1(char *string, int index)
{
	if (string[index + 1] == '\0'
		|| string[index + 1] == '-'
		|| string[index + 1] == '+'
		|| string[index + 1] == ')'
		|| string[index + 1] == '('
		|| string[index + 1] == '*'
		|| string[index + 1] == '&'
		|| string[index + 1] == '^'
		|| string[index + 1] == '%'
		|| string[index + 1] == '#'
		|| string[index + 1] == '@'
		|| string[index + 1] == '!'
		|| string[index + 1] == '"'
		|| string[index + 1] == 6)
	{
		string[index] = '$';
		return (FAILURE);
	}
	else
		return (SUCCESS);
}

static void	loop_while(int *index, int *tempnbr, char *string, char **result)
{
	*tempnbr = *index;
	while (string[*index] != '\0'
		&& string[*index] != '-'
		&& string[*index] != '+'
		&& string[*index] != ')'
		&& string[*index] != '('
		&& string[*index] != '*'
		&& string[*index] != '&'
		&& string[*index] != '^'
		&& string[*index] != '%'
		&& string[*index] != '#'
		&& string[*index] != '@'
		&& string[*index] != '!'
		&& string[*index] != '"')
		(*index)++;
	(result[2]) = utils_strdup(&(string[*index]));
	string[*index] = '\0';
	(result[1]) = utils_strdup(&(string[*tempnbr]));
	free(string);
}

static void	do_something(int *index, char **string, char **result)
{
	char	*env;
	int		tempnbr;

	(*index)++;
	result[0] = utils_strdup(*string);
	loop_while(index, &tempnbr, *string, result);
	if (utils_getenv(result[1]) == NULL)
		*string = utils_strjoin(result[0], "", result[2]);
	else
	{
		env = utils_getenv(result[1]);
		*string = utils_strjoin(result[0], env, result[2]);
		free(env);
	}
	free(result[0]);
	free(result[1]);
	free(result[2]);
}

void	parsin_global_variables(t_cmd_line **cmd_list)
{
	t_cmd_line	*tempnode;
	char		*result[3];
	int			index;

	tempnode = *cmd_list;
	while (tempnode)
	{
		if (utils_strstr(tempnode->data, "$"))
		{
			index = 0;
			while ((tempnode->data)[index] != '$')
				index++;
			(tempnode->data)[index] = '\0';
			if (condition_num1(tempnode->data, index))
			{
				tempnode = tempnode->next;
				continue ;
			}
			if (inside_single_quotes(tempnode->data))
				continue ;
			do_something(&index, &(tempnode->data), result);
		}
		tempnode = tempnode->next;
	}
}
