/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:41:24 by udumas            #+#    #+#             */
/*   Updated: 2024/05/30 19:29:07 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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