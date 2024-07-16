/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:08:49 by udumas            #+#    #+#             */
/*   Updated: 2024/07/16 16:54:24 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**ft_mult_mat(float **mat1, float **mat2, int free_data)
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
	if (free_data == FIRST)
		ft_free_mat(mat1, 4);
	if (free_data == SECOND)
		ft_free_mat(mat2, 4);
	if (free_data == ALL)
	{
		ft_free_mat(mat1, 4);
		ft_free_mat(mat2, 4);
	}
	return (res);
}

t_tuple	ft_mult_mat_tuple(t_tuple *tuple, float **mat, int free_data)
{
	t_tuple 	new;

	if (tuple == NULL || mat == NULL)
		return (*tuple);
	new.x = mat[0][0] *  tuple->x + mat[0][1] * tuple->y + mat[0][2] * tuple->z + mat[0][3] * tuple->w;
	new.y = mat[1][0] *  tuple->x + mat[1][1] * tuple->y + mat[1][2] * tuple->z + mat[1][3] * tuple->w;
	new.z = mat[2][0] *  tuple->x + mat[2][1] * tuple->y + mat[2][2] * tuple->z + mat[2][3] * tuple->w;
	new.w = mat[3][0] *  tuple->x + mat[3][1] * tuple->y + mat[3][2] * tuple->z + mat[3][3] * tuple->w;
	if (free_data == FIRST)
		free(tuple);
	if (free_data == SECOND)
		ft_free_mat(mat, 4);
	if (free_data == ALL)
	{
		free(tuple);
		ft_free_mat(mat, 4);
	}
	return (new);
}

float	**ft_transpose(float **mat)
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
	return (mat);
}

int	ft_comp_mat(float **mat1, float **mat2, int row_col)
{
	int	x;
	int	y;

	x = 0;
	while (x < row_col)
	{
		y = 0;
		while (y < row_col)
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
	{
		printf("Determinant is null\n");
		return (identity_matrix(4));
	}
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
