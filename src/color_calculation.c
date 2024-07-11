/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:30:27 by udumas            #+#    #+#             */
/*   Updated: 2024/07/10 18:46:09 by vda-conc         ###   ########.fr       */
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

t_color ft_mult_color(t_color c, float scalar)
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

t_color ft_color_reg(float r, float g, float b)
{
    t_color new;

    new.r = r;
    new.g = g;
    new.b = b;
    return (new);
}

t_color *ft_color(float r, float g, float b)
{
    t_color *new;

    new = malloc(sizeof(t_color));
    if (!new)
        return (NULL);
    new->r = r;
    new->g = g;
    new->b = b;
    return (new);
}
