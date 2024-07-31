/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:33:10 by udumas            #+#    #+#             */
/*   Updated: 2024/07/31 09:54:16 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	**identity_matrix(int size)
{
	t_norme_submat2	v;

	v.mat = malloc(sizeof(float *) * size);
	if (!v.mat)
		return (printf("malloc error\n"), NULL);
	v.i = -1;
	while (++v.i < size)
	{
		v.mat[v.i] = malloc(sizeof(float) * size);
		if (!v.mat[v.i])
			return (printf("malloc error\n"), NULL);
	}
	v.i = -1;
	while (++v.i < size)
	{
		v.j = -1;
		while (++v.j < size)
		{
			if (v.i == v.j)
				v.mat[v.i][v.j] = 1;
			else
				v.mat[v.i][v.j] = 0;
		}
	}
	return (v.mat);
}
