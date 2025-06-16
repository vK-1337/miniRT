/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_deter_cofac.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:13:02 by udumas            #+#    #+#             */
/*   Updated: 2024/07/29 17:41:33 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_deter2_2(float **mat)
{
	float	determinant;

	determinant = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	return (determinant);
}

float	ft_determinant3_3(float **mat)
{
	float	det;

	det = mat[0][0] * ((mat[1][1] * mat[2][2]) - (mat[2][1] * mat[1][2]))
		- mat[0][1] * ((mat[1][0] * mat[2][2]) - (mat[2][0] * mat[1][2]))
		+ mat[0][2] * ((mat[1][0] * mat[2][1]) - (mat[2][0] * mat[1][1]));
	return (det);
}

float	ft_cofactorinversion(float **mat, int row, int col)
{
	float	determinant;
	float	cofactor;
	float	**sub_mat;

	sub_mat = ft_submat(mat, 4, row, col);
	determinant = ft_determinant3_3(sub_mat);
	cofactor = pow(-1, row + col) * determinant;
	ft_free_mat(sub_mat, 3);
	return (cofactor);
}

float	ft_determinant4_4(float **matrice)
{
	float	det;
	float	sign;
	int		i;
	float	**mat;

	det = 0;
	sign = 1;
	i = 0;
	while (i < 4)
	{
		mat = ft_submat(matrice, 4, 0, i);
		det += sign * matrice[0][i] * ft_determinant3_3(mat);
		ft_free_mat(mat, 3);
		sign *= -1;
		i++;
	}
	return (det);
}

float	ft_cofactor2_2(float **mat, int row, int col)
{
	float	determinant;
	float	cofactor;

	determinant = ft_deter2_2(mat);
	cofactor = pow(-1, row + col) * determinant;
	return (cofactor);
}
