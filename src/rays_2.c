/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:38:16 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/29 18:39:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_sort_intersections(t_intersection *intersections, int count)
{
	int				i;
	int				j;
	t_intersection	tmp;

	i = 0;
	if (count == 1)
		intersections[0].count = count;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (intersections[i].t > intersections[j].t)
			{
				tmp = intersections[i];
				intersections[i] = intersections[j];
				intersections[j] = tmp;
			}
			intersections[i].count = count;
			j++;
		}
		i++;
	}
}

t_intersection	*ft_hit(t_intersection *intersections, int count)
{
	int	i;

	i = 0;
	if (intersections && intersections[0].status == 0)
		return (NULL);
	while (i < count && intersections)
	{
		if (intersections[i].t > 0.1)
			return (&intersections[i]);
		i++;
	}
	return (NULL);
}

t_ray	ray_transform(t_ray ray, float **matrix)
{
	t_ray	new_ray;

	new_ray.direction = ft_mult_matrix_tuple(matrix, &ray.direction, 4);
	new_ray.origin = ft_mult_matrix_tuple(matrix, &ray.origin, 4);
	ft_free_mat(matrix, 4);
	return (new_ray);
}

t_tuple	ft_mult_matrix_tuple(float **matrix, t_tuple *tuple, int free_id)
{
	t_tuple	new_tuple;

	new_tuple.x = matrix[0][0] * tuple->x + matrix[0][1] * tuple->y
		+ matrix[0][2] * tuple->z + matrix[0][3] * tuple->w;
	new_tuple.y = matrix[1][0] * tuple->x + matrix[1][1] * tuple->y
		+ matrix[1][2] * tuple->z + matrix[1][3] * tuple->w;
	new_tuple.z = matrix[2][0] * tuple->x + matrix[2][1] * tuple->y
		+ matrix[2][2] * tuple->z + matrix[2][3] * tuple->w;
	new_tuple.w = matrix[3][0] * tuple->x + matrix[3][1] * tuple->y
		+ matrix[3][2] * tuple->z + matrix[3][3] * tuple->w;
	if (free_id == FIRST)
		ft_free_mat(matrix, 4);
	if (free_id == SECOND)
		free(tuple);
	else if (free_id == ALL)
	{
		ft_free_mat(matrix, 4);
		free(tuple);
	}
	return (new_tuple);
}

void	set_transform(t_sphere *sphere, float **matrix)
{
	sphere->matrix = matrix;
	return ;
}
