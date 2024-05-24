/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:30:27 by udumas            #+#    #+#             */
/*   Updated: 2024/05/22 20:19:07 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	ft_sum_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r + c2.r;
	new.g = c1.g + c2.g;
	new.b = c1.b + c2.b;
    return (new);
}

t_color	ft_dif_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r - c2.r;
	new.g = c1.g - c2.g;
	new.b = c1.b - c2.b;
    return (new);
}

t_color ft_mult_color(t_color c, int scalar)
{
    t_color new;
    
    new.r = c.r * scalar;
    new.g = c.g * scalar;
    new.b = c.b * scalar;
    return (new);
}

t_color ft_mult_color_tog(t_color c1, t_color c2)
{
    t_color new;

    new.r = c1.r * c2.r;
    new.g = c1.g * c2.g;
    new.b = c1.b * c2.b;
    return (new);
}