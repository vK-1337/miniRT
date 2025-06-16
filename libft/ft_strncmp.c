/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:28:21 by vk                #+#    #+#             */
/*   Updated: 2024/05/21 18:32:27 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	if ((!first && !second) || length == 0)
		return (0);
	i = 0;
	while (i < length && (first[i] || second[i]))
	{
		if (first[i] != second[i])
			return ((unsigned char)(first[i]) - (unsigned char)(second[i]));
		i++;
	}
	return (0);
}
