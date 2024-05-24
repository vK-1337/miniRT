/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:08:49 by udumas            #+#    #+#             */
/*   Updated: 2024/05/24 15:30:36 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**ft_matcre(float *tab, int row_col)
{
	int i;
	int j;
	int k;
	float **matrice;
	
	i = -1;
	k = 0;
	matrice = malloc(sizeof(float *) * row_col);
	if (!matrice)
		return (printf("malloc error\n"), NULL);
	while (++i < row_col)
	{
		matrice[i] = malloc(sizeof(float) * row_col);
		if (!matrice[i])
			return (printf("malloc error\n"), NULL);
	}
	i = -1;
	while (++i < row_col)
	{
		j = -1;
		while (++j < row_col)
			matrice[i][j] = tab[k++];	
	}
	return (matrice);
}

void	ft_mult_mat(float res[4][4], float mat1[4][4], float mat2[4][4])
{
	int	row;
	int	col;

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
}

void	ft_mult_mat_tuple(float tuple[4], float mat[4][4])
{
	int row;

	row = 0;
	while (row < 4)
	{
		tuple[row] = mat[row][0] * tuple[0] + mat[row][1] * tuple[1]
			+ mat[row][2] * tuple[2] + mat[row][3] * tuple[3];
		row++;
	}
}
