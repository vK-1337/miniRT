/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:42:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/06/08 11:51:32 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple ft_reflect(t_tuple in, t_tuple normal)
{
    return (ft_dif_tuple(in, ft_mult_vector(normal, 2 * ft_dotproduct(in, normal))));
}

t_tuple ft_normal_at(t_comps object, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    float **matrix;

    if (object.type == SPHERE)
    {
        matrix = object.sphere->matrix;
        object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), world_point);
        object_normal = ft_dif_tuple(object_point, *ft_init_tuple(0, 0, 0, 1));
    }
    else if (object.type == PLAN)
    {
        matrix = object.plan->matrix;
        object_normal = object.plan->normal;
    }
    else if (object.type == CYLINDER)
    {
        matrix = object.cylinder->matrix;   
        object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), world_point);
        float dist = object_point.x * object_point.x + object_point.z * object_point.z;
        if (dist < 1 && (object_point.y >= (object.cylinder->y_max - EPSILON)))
            object_normal = *ft_init_tuple(0, 1, 0, 0);
        else if (dist < 1 && (object_point.y <= (object.cylinder->y_min + EPSILON)))
            object_normal = *ft_init_tuple(0, -1, 0, 0);
        else
            object_normal = *ft_init_tuple(object_point.x, 0, object_point.z, 0);
    }
    else if (object.type == CONE)
    {
        matrix = object.cone->matrix;
        object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), world_point);
        float y = sqrt(object_point.x * object_point.x + object_point.z * object_point.z);
        if (object_point.y > 0)
           y = -y;
        object_normal = *ft_init_tuple(object_point.x, y, object_point.z, 0);
    }
    else
    {
        object_normal = *ft_init_tuple(0, 0, 0, 0);
        matrix = identity_matrix(4);
    }
    world_normal = ft_mult_matrix_tuple(ft_transpose(ft_inversion(matrix, 4)), object_normal);
    
    world_normal.w = 0;
    return (ft_normalization(world_normal));
}
