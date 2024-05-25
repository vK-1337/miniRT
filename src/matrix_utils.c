/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:10:22 by udumas            #+#    #+#             */
/*   Updated: 2024/05/25 15:15:39 by udumas           ###   ########.fr       */
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

void ft_free_mat(float **mat, int row_col)
{
	int i;

	i = 0;
	while (i < row_col)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

float **ft_create_mat_null(int row_col)
{
	float **new_mat;
	int i;
	int j;

	new_mat = malloc(sizeof(float *) * row_col);
	i = 0;
	while (i < row_col)
	{
		new_mat[i] = malloc(sizeof(float) * row_col);
		j = 0;
		while (j < row_col)
		{
			new_mat[i][j] = 0;
			j++;
		}
		i++;
	}
	return (new_mat);
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
	new_mat = malloc(sizeof(float *) * (row_col - 1));
	if (!new_mat)
		return (printf("Erreur malloc\n"), NULL);
	while (++i < row_col - 1)
	{
		new_mat[i] = malloc(sizeof(float) * (row_col - 1));
		if (!new_mat[i])
			return (printf("Erreur malloc\n"), NULL);
	}
	i = -1;
	while (++i < row_col)
	{
		if (i == row)
			continue ;
		j = -1;
		l = 0;
		while (++j < row_col)
		{
			if (j != col)
				new_mat[k][l++] = matrice[i][j];
		}
		k++;
	}
	return (new_mat);
}


