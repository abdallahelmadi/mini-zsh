/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_docente.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:30:20 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/27 14:05:45 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	utils_docente(const char *origin, int index, char c)
{
	int	inside;
	int	indexo;

	inside = 0;
	indexo = 0;
	while (index > indexo)
	{
		if (origin[indexo] == c)
			inside++;
		indexo++;
	}
	if (inside == 0 || (inside > 1 && inside % 2 == 0))
		return (SUCCESS);
	return (FAILURE);
}
