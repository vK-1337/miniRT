/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:42:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 15:54:34 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	ft_reflect(t_tuple in, t_tuple normal)
{
	return (ft_dif_tuple(in, ft_mult_vector(normal, 2 * ft_dotproduct(in,
					normal))));
}

t_tuple	ft_normal_at(t_comps object, t_tuple world_point)
{
	t_tuple	object_normal;
	t_tuple	world_normal;
	float	**matrix;

	if (object.type == SPHERE)
		object_normal = calculate_sphere_normal(object, world_point, &matrix);
	else if (object.type == PLAN)
	{
		matrix = object.plan->matrix;
		object_normal = object.plan->normal;
	}
	else if (object.type == CYLINDER)
		object_normal = calculate_cylinder_normal(object, world_point, &matrix);
	else if (object.type == CONE)
		object_normal = calculate_cone_normal(object, world_point, &matrix);
	else
	{
		object_normal = ft_init_tuple_reg(0, 0, 0, 0);
		matrix = identity_matrix(4);
	}
	world_normal = ft_mult_matrix_tuple(ft_transpose(ft_inversion(matrix, 4)),
			&object_normal, FIRST);
	world_normal.w = 0;
	return (ft_normalization(world_normal));
}

t_tuple	calculate_sphere_normal(t_comps object, t_tuple world_point,
		float ***attr_mat)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	float	**matrix;

	matrix = object.sphere->matrix;
	*attr_mat = matrix;
	object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), &world_point,
			FIRST);
	object_normal = ft_dif_tuple(object_point, ft_init_tuple_reg(0, 0, 0, 1));
	return (object_normal);
}

t_tuple	calculate_cylinder_normal(t_comps object, t_tuple world_point,
		float ***attr_mat)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	float	**matrix;
	float	dist;

	matrix = object.cylinder->matrix;
	*attr_mat = matrix;
	object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), &world_point,
			FIRST);
	dist = object_point.x * object_point.x + object_point.z * object_point.z;
	if (dist < pow(object.cylinder->radius, 2)
		&& (object_point.y >= (object.cylinder->y_max - EPSILON)))
		object_normal = ft_init_tuple_reg(0, 1, 0, 0);
	else if (dist < pow(object.cylinder->radius, 2)
		&& (object_point.y <= (object.cylinder->y_min + EPSILON)))
		object_normal = ft_init_tuple_reg(0, -1, 0, 0);
	else
		object_normal = ft_init_tuple_reg(object_point.x, 0, object_point.z, 0);
	return (object_normal);
}

t_tuple	calculate_cone_normal(t_comps object, t_tuple world_point,
		float ***attr_mat)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	float	**matrix;
	float	dist;
	float	y;

	matrix = object.cone->matrix;
	*attr_mat = matrix;
	object_point = ft_mult_matrix_tuple(ft_inversion(matrix, 4), &world_point,
			FIRST);
	dist = object_point.x * object_point.x + object_point.z * object_point.z;
	y = sqrt(dist);
	if (dist < pow(object.cone->y_max, 2)
		&& (object_point.y >= (object.cone->y_max - EPSILON)))
		object_normal = ft_init_tuple_reg(0, 1, 0, 0);
	else if (dist < pow(object.cone->y_min, 2)
		&& (object_point.y <= (object.cone->y_min + EPSILON)))
		object_normal = ft_init_tuple_reg(0, -1, 0, 0);
	else
	{
		object_normal = ft_init_tuple_reg(object_point.x, y, object_point.z, 0);
		if (object_point.y > 0)
			object_normal.y = -y;
	}
	return (object_normal);
}
