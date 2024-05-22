/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:42:02 by udumas            #+#    #+#             */
/*   Updated: 2024/05/22 20:36:17 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_transpose(float mat[4][4])
{
    int i;
    int j;
    float temp;

    i = 0;
    while (i < 4)
    {
        j = i + 1;
        while (j < 4)
        {
            temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
            j++;
        }
        i++;
    }
}

int ft_comp_mat(float mat1[4][4], float mat2[4][4])
{
    int x;
    int y;
    
    x = 0;
    while (x < 4)
    {
        y = 0;
        while (y < 4)
        {
            if (ft_comp_float(mat1[y][x], mat2[y][x]) == 0)
                return (0);  
          y++;  
        }
        x++;
    }
    return (1);
}

void print_matrix(float mat[4][4])
{
    int x, y;

    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            printf("%f ", mat[y][x]);
        }
        printf("\n");
    }
}

int ft_deter2_2(float mat[2][2])
{
    int determinant;

    determinant = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    return (determinant);
}

int main()
{
    // float mat1[4][4];
    // float mat2[4][4];
    // float list[16] = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
    // float list2[16] = {1,2,0,4,5,6,7,8,9,8,7,6,5,4,3,2};
    // ft_matcre4_4(mat1, list);
    // ft_matcre4_4(mat2, list2);
    // float res[4][4];
    // ft_mult_mat(res, mat1, mat2);
    float mat[2][2];
    float list[4] = {1,5,-3,2};
    ft_matcre2_2(mat, list);
    ft_deter2_2(mat);
    printf("are they equal = %d\n", ft_deter2_2(mat));
    
}
