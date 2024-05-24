/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:06:26 by vk                #+#    #+#             */
/*   Updated: 2024/05/21 18:32:27 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isneg(long n)
{
	if (n < 0)
		return (1);
	return (0);
}

size_t	ft_nbrlen(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		neg;
	char	*number;
	long	nbr;

	nbr = n;
	neg = ft_isneg(nbr);
	if (n < 0)
		nbr *= -1;
	len = ft_nbrlen(nbr);
	number = malloc((len + 1 + neg) * sizeof(char));
	if (!number)
		return (NULL);
	if (n < 0)
		number[0] = '-';
	number[len + neg] = '\0';
	while (len > 0)
	{
		if (n >= 0)
			number[(len--) - 1] = ((nbr % 10) + '0');
		else
			number[(len--)] = ((nbr % 10) + '0');
		nbr /= 10;
	}
	return (number);
}
