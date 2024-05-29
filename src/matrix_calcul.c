/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:08:49 by udumas            #+#    #+#             */
/*   Updated: 2024/05/29 09:40:24 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**ft_mult_mat(float **mat1, float **mat2)
{
	int		row;
	int		col;
	float	**res;

	res = ft_create_mat_null(4);
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			res[row][col] = mat1[row][0] * mat2[0][col] + mat1[row][1]
				* mat2[1][col] + mat1[row][2] * mat2[2][col] + mat1[row][3]
				* mat2[3][col];
			col++;
		}
		row++;
	}
	return (res);
}

t_tuple	ft_mult_mat_tuple(t_tuple *tuple, float **mat)
{
	t_tuple 	new;

	new.x = mat[0][0] *  tuple->x + mat[0][1] * tuple->y + mat[0][2] * tuple->z + mat[0][3] * tuple->w;
	new.y = mat[1][0] *  tuple->x + mat[1][1] * tuple->y + mat[1][2] * tuple->z + mat[1][3] * tuple->w;
	new.z = mat[2][0] *  tuple->x + mat[2][1] * tuple->y + mat[2][2] * tuple->z + mat[2][3] * tuple->w;
	new.w = mat[3][0] *  tuple->x + mat[3][1] * tuple->y + mat[3][2] * tuple->z + mat[3][3] * tuple->w;
	return (new);
}

void	ft_transpose(float mat[4][4])
{
	int		i;
	int		j;
	float	temp;

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

int	ft_comp_mat(float mat1[4][4], float mat2[4][4])
{
	int	x;
	int	y;

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

float	**ft_inversion(float **matrice, int row_col)
{
	float	det;
	float	**mat;
	int		i;
	int		j;
	float	temp;

	i = 0;
	j = 0;
	det = ft_determinant4_4(matrice);
	if (det == 0)
		return (NULL);
	mat = ft_create_mat_null(4);
	while (i < row_col)
	{
		j = 0;
		while (j < row_col)
		{
			temp = ft_cofactorinversion(matrice, i, j);
			mat[j][i] = temp / det;
			j++;
		}
		i++;
	}
	return (mat);
}
