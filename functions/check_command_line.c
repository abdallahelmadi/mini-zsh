/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/15 17:48:46 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	*new_node(char *data)
{
	t_cmd_line	*cmd;

	cmd = malloc(sizeof(t_cmd_line));
	if (cmd == NULL)
		return (NULL);
	cmd->data = utils_strdup(data);
	cmd->next = NULL;
	return (cmd);
}

static t_cmd_line	*last_node(t_cmd_line *header)
{
	t_cmd_line	*temp;
	t_cmd_line	*rurn;

	temp = header;
	while (temp != NULL)
	{
		rurn = temp;
		temp = temp->next;
	}
	return (rurn);
}

static void	free_double_pointer(char **array)
{
	int	index;

	index = 0;
	while (array != NULL && array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static void	free_linked_list(t_cmd_line *header)
{
	t_cmd_line	*temp;

	while (header != NULL)
	{
		free(header->data);
		temp = header;
		header = header->next;
		free(temp);
	}
}

static t_cmd_line	*split_command_as_list(const char *command_line)
{
	char		**temp;
	int			index;
	int			lenght_of_array;
	t_cmd_line	*node;
	t_cmd_line	*node_temp;

	temp = NULL;
	node = NULL;
	index = 0;
	lenght_of_array = 0;
	if (!utils_strcmp(command_line, '|'))
	{
		temp = utils_split(command_line, '|');
		node = new_node(temp[index]);
		index++;
		while (temp[index] != NULL)
		{
			last_node(node)->next = new_node("|");
			last_node(node)->next = new_node(temp[index]);
			index++;
		}
	}
	while (temp != NULL && temp[lenght_of_array] != NULL)
		lenght_of_array++;
	if (lenght_of_array > 0)
	{
		free_double_pointer(temp);
		if (utils_strstr(command_line, "<<"))
		{
			node_temp = node;
			while (node_temp != NULL)
			{
				temp = utils_split_pro(node_temp->data, "<<");
				node_temp = node_temp->next;
				node_temp = node_temp->next;
				index++;

				int x = 0;
				while (temp[x] != NULL)
				{
					printf("[%s] -> ", temp[x]);
					x++;
				}
			}
		}
	}
	return (node);
}

void	check_command_line(const char *command_line)
{
	t_cmd_line	*cmd_list;

	if (command_line[0] == '\0')
		return ;
	else if (!utils_strcmp(command_line, '&') || utils_strstr(command_line, ">>>")
		|| !utils_strcmp(command_line, '(') || !utils_strcmp(command_line, ')')
		|| !utils_strcmp(command_line, '*') || !utils_strcmp(command_line, ';')
		|| utils_strstr(command_line, "<<<") || !utils_strcmp(command_line, '#')
		|| !utils_strcmp(command_line, '\\')
		|| utils_strstr(command_line, "||"))
	{
		printf("minishell: something unsupported\n");
		g_lastexitstatus = FAILURE;
	}
	else
	{
		cmd_list = split_command_as_list(command_line);
		while (cmd_list != NULL)
		{
			printf("[%s] -> ", cmd_list->data);
			cmd_list = cmd_list->next;
		}
		printf("\n");
		free_linked_list(cmd_list);
		g_lastexitstatus = SUCCESS;
	}
}
