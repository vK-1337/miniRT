/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:56:18 by udumas            #+#    #+#             */
/*   Updated: 2024/05/29 09:49:25 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


float **translation(float x, float y, float z)
{
    float **mat;

    mat = identity_matrix(4);
    mat[0][3] = x;
    mat[1][3] = y;
    mat[2][3] = z;
    return (mat);
}

float   **scaling(float x, float y, float z)
{
    float **mat;

    mat = identity_matrix(4);
    mat[0][0] = x;
    mat[1][1] = y;
    mat[2][2] = z;
    return (mat);
}

void    rotation_x(t_tuple *t, float rad)
{
    float **mat;

    mat = identity_matrix(4);
    mat[1][1] = cos(rad);
    mat[1][2] = -sin(rad);
    mat[2][1] = sin(rad);
    mat[2][2] = cos(rad);
    ft_mult_mat_tuple(t, mat);
    free(mat);
    return ;
}

void    rotation_y(t_tuple *t, float rad)
{
    float **mat;

    mat = identity_matrix(4);
    mat[0][0] = cos(rad);
    mat[0][2] = sin(rad);
    mat[2][0] = -sin(rad);
    mat[2][2] = cos(rad);
    *t = ft_mult_mat_tuple(t, mat);
    free(mat);
    return ;
}

void rotation_z(t_tuple *t, float rad)
{
    float **mat;
    
    mat = identity_matrix(4);
    mat[0][0] = cos(rad);
    mat[0][1] = -sin(rad);
    mat[1][0] = sin(rad);
    mat[1][1] = cos(rad);
    ft_mult_mat_tuple(t, mat);
    free(mat);
    return ;
}


// int main()
// {
// 	float **mat1;
//     float **inv;
//     t_tuple v;
    
// 	mat1 = scaling(-1,1,1);
//     v = ft_init_tuple(2,3,4,1);
//     // inv = ft_inversion(mat1, 4);
//     ft_mult_mat_tuple(&v, mat1);
//     printf("x = %f, y = %f, z = %f, w = %f\n", v.x, v.y, v.z, v.w);
//     return (0);
// }