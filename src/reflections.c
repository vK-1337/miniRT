/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:42:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/30 19:31:47 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple ft_reflect(t_tuple in, t_tuple normal)
{
    return (ft_dif_tuple(in, ft_mult_vector(normal, 2 * ft_dotproduct(in, normal))));
}

t_tuple ft_normal_at(t_sphere sphere, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    
    object_point = ft_mult_matrix_tuple(ft_inversion(sphere.matrix, 4), world_point);
    object_normal = ft_dif_tuple(object_point, *ft_init_tuple(0, 0, 0, 1));
    world_normal = ft_mult_matrix_tuple(ft_transpose(ft_inversion(sphere.matrix, 4)), object_normal);
    world_normal.w = 0;
    return (ft_normalization(world_normal));
}