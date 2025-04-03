/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strncmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:53:02 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/03 18:16:10 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	utils_strncmp(const char *s1, const char *s2, int size)
{
	int	index;

	index = 0;
	while (size > index && s1[index] != '\0' && s2[index] != '\0'
		&& s1[index] == s2[index])
		index++;
	if (size == index)
		return (SUCCESS);
	return (s1[index] - s2[index]);
}
