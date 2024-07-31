/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:48:53 by udumas            #+#    #+#             */
/*   Updated: 2024/07/29 17:49:43 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**shearing(float shear[6])
{
	float	**mat;

	mat = identity_matrix(4);
	mat[0][1] = shear[0];
	mat[0][2] = shear[1];
	mat[1][0] = shear[2];
	mat[1][2] = shear[3];
	mat[2][0] = shear[4];
	mat[2][1] = shear[5];
	return (mat);
}
