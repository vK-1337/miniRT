/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 09:35:50 by vk                #+#    #+#             */
/*   Updated: 2024/05/21 18:32:27 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	if (!string)
		return ((void *) NULL);
	while (string[i])
	{
		if (string[i] == (char)searchedChar)
			return ((char *)(string + i));
		i++;
	}
	if (string[i] == (char)searchedChar)
		return ((char *)(string + i));
	return ((void *) NULL);
}
