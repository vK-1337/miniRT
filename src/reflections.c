/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:12:34 by udumas            #+#    #+#             */
/*   Updated: 2024/05/29 18:32:59 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


t_tuple ft_normal_at(t_sphere sphere, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    
    object_point = ft_mult_matrix_tuple(ft_inversion(sphere.matrix, 4), world_point);
    object_normal = ft_dif_tuple(object_point, ft_init_tuple(0, 0, 0, 1));
    world_normal = ft_mult_matrix_tuple(ft_transpose(ft_inversion(sphere.matrix, 4)), object_normal);
    world_normal.w = 0;
    return (ft_normalization(world_normal));
}
// int main()
// {
//     t_sphere s;
//     t_tuple n;
//     float **mat;
    
//     s = ft_sphere();
//     mat = translation(0,1,0);
//     set_transform(&s, mat);
//     n = ft_normal_at(s, ft_init_tuple(0, 1.70711, -0.70711, 1));
//     printf("vector n =\nx = %f\ny = %f\nz = %f\nw = %f\n", n.x, n.y,n.z,n.w);
// }