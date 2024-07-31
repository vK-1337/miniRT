/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:13:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 09:34:28 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	get_cone_discriminant(t_ray ray, float abc[3])
{
	float	discriminant;

	abc[0] = ray.direction.x * ray.direction.x - ray.direction.y
		* ray.direction.y + ray.direction.z * ray.direction.z;
	abc[1] = 2 * ray.direction.x * ray.origin.x - 2 * ray.direction.y
		* ray.origin.y + 2 * ray.direction.z * ray.origin.z;
	abc[2] = ray.origin.x * ray.origin.x - ray.origin.y * ray.origin.y
		+ ray.origin.z * ray.origin.z;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	return (discriminant);
}

void	ft_cone_intersect(t_intersection **t_tab, t_cone **cone, t_ray ray,
		int *count)
{
	t_norme_cone	v;

	if (!*cone)
		return ;
	v.new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
	v.discriminant = get_cone_discriminant(v.new_ray, v.abc);
	if (v.discriminant < 0)
		return ;
	if (fabsf(v.abc[0]) < EPSILON && fabsf(v.abc[1]) > EPSILON)
	{
		v.t.t = -v.abc[2] / (2 * v.abc[1]);
		attribute_cone(&v.t, count, *cone);
		*t_tab = ft_add_one_t(t_tab, v.t, *count);
		return ;
	}
	cone_intersect_helper(&v, cone);
	if (v.y0 < (*cone)->y_max && v.y0 > (*cone)->y_min)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, v.t, *count);
	}
	v.t.t = (-v.abc[1] + v.discriminant) / (2 * v.abc[0]);
	v.y0 = v.new_ray.origin.y + v.t.t * v.new_ray.direction.y;
	cone_intersect_helper2(&v, count, cone, t_tab);
}

void	cone_intersect_helper(t_norme_cone *v, t_cone **cone)
{
	v->discriminant = sqrt(v->discriminant);
	v->t.t = (-v->abc[1] - v->discriminant) / (2 * v->abc[0]);
	v->t.cone = *cone;
	v->t.sphere = NULL;
	v->t.plan = NULL;
	v->t.cylinder = NULL;
	v->y0 = v->new_ray.origin.y + v->t.t * v->new_ray.direction.y;
}

void	cone_intersect_helper2(t_norme_cone *v, int *count, t_cone **cone,
		t_intersection **t_tab)
{
	if (v->y0 < (*cone)->y_max && v->y0 > (*cone)->y_min)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, v->t, *count);
	}
}

t_cone	*ft_cone(void)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->radius = 1;
	cone->y_max = 1;
	cone->y_min = 0;
	cone->matrix = identity_matrix(4);
	cone->m = ft_material();
	cone->next = NULL;
	return (cone);
}
