/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:51:28 by bainur            #+#    #+#             */
/*   Updated: 2024/07/31 09:13:28 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	within_cone_radius(const t_ray *ray, double t, double cone_val)
{
	double	x;
	double	z;

	x = ray->origin.x + ray->direction.x * t;
	z = ray->origin.z + ray->direction.z * t;
	cone_val = fabs(cone_val);
	if ((x * x + z * z) <= (cone_val * cone_val))
		return (1);
	return (0);
}

void	ft_check_cone_caps(t_intersection **t_tab, t_cone **cone, t_ray ray,
		int *count)
{
	t_intersection	t;
	t_ray			new_ray;

	if (!*cone)
		return ;
	new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
	if (fabsf(new_ray.direction.y) < EPSILON)
	{
		*cone = (*cone)->next;
		return ;
	}
	t.t = ((*cone)->y_max - new_ray.origin.y) / new_ray.direction.y;
	if (within_cone_radius(&new_ray, t.t, (*cone)->y_max) == 1)
	{
		attribute_cone(&t, count, *cone);
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
	t.t = ((*cone)->y_min - new_ray.origin.y) / new_ray.direction.y;
	if (within_cone_radius(&new_ray, t.t, (*cone)->y_min) == 1)
	{
		attribute_cone(&t, count, *cone);
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
	*cone = (*cone)->next;
}

void	attribute_cone(t_intersection *t, int *count, t_cone *cone)
{
	t->cone = cone;
	t->sphere = NULL;
	t->plan = NULL;
	t->cylinder = NULL;
	*count += 1;
}
