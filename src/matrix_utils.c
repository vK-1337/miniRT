/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:10:22 by udumas            #+#    #+#             */
/*   Updated: 2024/07/31 09:50:40 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**ft_matcre(float *tab, int row_col)
{
	int		i;
	int		j;
	int		k;
	float	**matrice;

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

void	ft_free_mat(float **mat, int row_col)
{
	int	i;

	i = 0;
	while (i < row_col)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

float	**ft_create_mat_null(int row_col)
{
	float	**new_mat;
	int		i;
	int		j;

	new_mat = malloc(sizeof(float *) * row_col);
	if (!new_mat)
		return (NULL);
	i = 0;
	while (i < row_col)
	{
		new_mat[i] = malloc(sizeof(float) * row_col);
		if (!new_mat[i])
			return (NULL);
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

float	**ft_submat(float **matrice, int row_col, int row, int col)
{
	float			**new_mat;
	t_norme_submat	v;

	v.i = -1;
	v.k = 0;
	v.l = 0;
	v.row = row;
	v.col = col;
	if (matrice == NULL)
		return (NULL);
	new_mat = malloc(sizeof(float *) * (row_col - 1));
	if (!new_mat)
		return (printf("Erreur malloc\n"), NULL);
	while (++v.i < row_col - 1)
	{
		new_mat[v.i] = malloc(sizeof(float) * (row_col - 1));
		if (!new_mat[v.i])
			return (printf("Erreur malloc\n"), NULL);
	}
	submat_helper(new_mat, matrice, row_col, v);
	return (new_mat);
}

void	submat_helper(float **new_mat, float **matrice, int row_col,
		t_norme_submat v)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	k = 0;
	l = 0;
	while (++i < row_col)
	{
		if (i == v.row)
			continue ;
		j = -1;
		l = 0;
		while (++j < row_col)
		{
			if (j != v.col)
				new_mat[k][l++] = matrice[i][j];
		}
		k++;
	}
}
