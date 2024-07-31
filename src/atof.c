/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:42:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:15:43 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	ft_atof(char *str)
{
	double	res;
	double	dec;
	int		sign;
	int		i;

	res = 0.0;
	dec = 10.0;
	sign = 1;
	atof_util(&i, &sign, str);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			res = res + (str[i] - '0') / dec;
			dec *= 10.0;
			i++;
		}
	}
	return (res * sign);
}

void	atof_util(int *i, int *sign, char *str)
{
	*i = 0;
	*sign = 1;
	if (str[*i] == '-')
	{
		*sign = -1;
		*i = 1;
	}
}
