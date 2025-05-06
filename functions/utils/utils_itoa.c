/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:49:51 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 10:20:12 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*utils_itoa(int nbr)
{
	char	*result;

	result = smalloc(sizeof(char) * 4);
	if (10 > nbr)
	{
		result[0] = (nbr + 48);
		result[1] = '\0';
	}
	else if (nbr > 9 && 100 > nbr)
	{
		result[0] = (nbr / 10) + 48;
		result[1] = (nbr % 10) + 48;
		result[2] = '\0';
	}
	else if (nbr > 99)
	{
		result[0] = (nbr / 100) + 48;
		nbr = nbr % 100;
		result[1] = (nbr / 10) + 48;
		result[2] = (nbr % 10) + 48;
		result[3] = '\0';
	}
	else
		return (NULL);
	return (result);
}
