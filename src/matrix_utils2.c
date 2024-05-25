/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:33:10 by udumas            #+#    #+#             */
/*   Updated: 2024/05/25 15:34:58 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float **identity_matrix(int size)
{
    float **mat;
    int i;
    int j;

    mat = malloc(sizeof(float *) * size);
    if (!mat)
        return (printf("malloc error\n"), NULL);
    i = -1;
    while (++i < size)
    {
        mat[i] = malloc(sizeof(float) * size);
        if (!mat[i])
            return (printf("malloc error\n"), NULL);
    }
    i = -1;
    while (++i < size)
    {
        j = -1;
        while (++j < size)
        {
            if (i == j)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
    return (mat);
}
