/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:23:40 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:18:30 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	utils_strlen(const char *string)
{
	size_t	count;

	count = 0;
	while (string[count] != '\0')
		count++;
	return (count);
}
