/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:33:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/13 14:44:36 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_all(t_smalloc_addr **smalloc_addr_v)
{
	t_smalloc_addr	*tempnode;

	while (*smalloc_addr_v)
	{
		tempnode = *smalloc_addr_v;
		*smalloc_addr_v = (*smalloc_addr_v)->next;
		if (tempnode->address)
			free(tempnode->address);
		if (tempnode)
			free(tempnode);
	}
	g_global.g_smalloc_addr_v = NULL;
}

static void	link_all(t_smalloc_addr **smalloc_addr_v, void	**dalloc)
{
	t_smalloc_addr	*tempnode;

	tempnode = *smalloc_addr_v;
	while (tempnode->next)
		tempnode = tempnode->next;
	tempnode->next = malloc(sizeof(t_smalloc_addr));
	tempnode->next->address = *dalloc;
	tempnode->next->next = NULL;
}

void	*smalloc(int size)
{
	static t_smalloc_addr	*smalloc_addr_v;
	void					*dalloc;

	smalloc_addr_v = g_global.g_smalloc_addr_v;
	if (size == -1)
	{
		free_all(&smalloc_addr_v);
		g_global.g_smalloc_addr_v = NULL;
		return (NULL);
	}
	dalloc = malloc(size);
	if (dalloc == NULL)
	{
		free_all(&smalloc_addr_v);
		exit(1);
	}
	if (smalloc_addr_v == NULL)
	{
		g_global.g_smalloc_addr_v = malloc(sizeof(t_smalloc_addr));
		g_global.g_smalloc_addr_v->address = dalloc;
		g_global.g_smalloc_addr_v->next = NULL;
	}
	else
		link_all(&smalloc_addr_v, &dalloc);
	return (dalloc);
}
