/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:42:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/11 14:04:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minirt.h"

double ft_atof(char *str)
{
    double res;
    double dec;
    int sign;
    int i;

    res = 0.0;
    dec = 10.0;
    sign = 1;
    i = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
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
