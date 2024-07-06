/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:24 by udumas            #+#    #+#             */
/*   Updated: 2024/07/04 16:50:43 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


t_tuple ft_init_tuple_reg(float x, float y, float z, float w)
{
    t_tuple tuple;

    tuple.x = x;
    tuple.y = y;
    tuple.z = z;
    tuple.w = w;
    return (tuple);
}

t_tuple *ft_init_tuple(float x, float y, float z, float w)
{
   t_tuple *tuple;

    tuple = malloc(sizeof(t_tuple));
    tuple->x = x;
    tuple->y = y;
    tuple->z = z;
    tuple->w = w;
    return (tuple);
}

int ft_equal_tuple(t_tuple *t1, t_tuple *t2)
{
    if (t1->x == t2->x && t1->y == t2->y && t1->z == t2->z && t1->w == t2->w)
        return (1);
    return (0);
}