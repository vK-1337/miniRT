/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:42:02 by udumas            #+#    #+#             */
/*   Updated: 2024/05/24 17:12:45 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

float	ft_deter2_2(float mat[2][2])
{
	float	determinant;

	determinant = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	return (determinant);
}

float	**ft_submat(float **matrice, int row_col, int row, int col)
{
	float	**new_mat;
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	k = 0;
	l = 0;
	new_mat = malloc(sizeof(float *) * row_col - 1);
	if (!new_mat)
		return (printf("Erreur malloc\n"), NULL);
	while (++i < row_col - 1)
	{
		new_mat[i] = malloc(sizeof(float) * row_col - 1);
		if (!new_mat[i])
			return (printf("Erreur malloc\n"), NULL);
	}
	i = -1;
	while (++i < row_col)
	{
		if (i == row - 1)
			continue ;
		j = -1;
        l = 0;
		while (++j < row_col)
		{
			if (j != col - 1)
				new_mat[i][j] = matrice[k][l++];
		}
        k++;
	}
	return (new_mat);
}

float determinant(float mat[3][3])
{
    float det;
    det = mat[0][0] * ((mat[1][1]*mat[2][2]) - (mat[2][1]*mat[1][2])) 
        - mat[0][1] * ((mat[1][0]*mat[2][2]) - (mat[2][0]*mat[1][2])) 
        + mat[0][2] * ((mat[1][0]*mat[2][1]) - (mat[2][0]*mat[1][1]));
    return det;
}

void	print_matrix(float **mat, int row_col)
{
	int x, y;
	for (y = 0; y < row_col; y++)
	{
		for (x = 0; x < row_col; x++)
		{
			printf("%f ", mat[y][x]);
		}
		printf("\n");
	}
}

int	main(void)
{
	float	**matrice;
	float	**mat2;
	float	tab[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int		i;

	matrice = ft_matcre(tab, 3);
	print_matrix(matrice, 3);
	mat2 = ft_submat(matrice, 3, 3, 3);
	print_matrix(mat2, 2);
	i = 0;
	while (i < 2)
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}
