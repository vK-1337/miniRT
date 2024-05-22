/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:08:49 by udumas            #+#    #+#             */
/*   Updated: 2024/05/22 21:19:00 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_matcre2_2(float **mat, float arr[4])
{
	int	x;
	int	y;
	int	k;
 
	k = 0;
	y = 0;
	while (y < 2)
	{
		x = 0;
		while (x < 2)
		{
			mat[y][x] = arr[k++];
			x++;
		}
		y++;
	}
}

void	ft_matcre3_3(float mat[3][3], float arr[9])
{
	int	x;
	int	y;
	int	k;

	k = 0;
	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			mat[y][x] = arr[k++];
			x++;
		}
		y++;
	}
}

void	ft_matcre4_4(float mat[4][4], float arr[16])
{
	int	x;
	int	y;
	int	k;

	k = 0;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			mat[y][x] = arr[k++];
			x++;
		}
		y++;
	}
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