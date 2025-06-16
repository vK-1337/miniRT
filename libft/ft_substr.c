/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:44:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/21 18:32:27 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (start > ft_strlen(s))
	{
		p = malloc(sizeof(char));
		*p = 0;
		return (p);
	}
	i = ft_strlen(&s[start]);
	if (len < i)
		p = malloc((len + 1) * sizeof(char));
	else
		p = malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

// int main()
// {
//     char *disp;

//     disp = ft_substr("tripouille", 1, 1);
//     printf("%s", disp);
//     free(disp);
// }

// // Alloue (avec malloc(3)) et retourne une chaîne de
// caractères issue de la chaîne ’s’.
// Cette nouvelle chaîne commence à l’index ’start’ et
// a pour taille maximale ’len’.