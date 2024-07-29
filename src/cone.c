/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:51:28 by bainur            #+#    #+#             */
/*   Updated: 2024/07/29 17:51:51 by vda-conc         ###   ########.fr       */
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
	{
		return ;
	}
	new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
	if (fabsf(new_ray.direction.y) < EPSILON)
	{
		*cone = (*cone)->next;
		return ;
	}
	t.t = ((*cone)->y_max - new_ray.origin.y) / new_ray.direction.y;
	if (within_cone_radius(&new_ray, t.t, (*cone)->y_max) == 1)
	{
		t.cone = *cone;
		t.sphere = NULL;
		t.plan = NULL;
		t.cylinder = NULL;
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
	t.t = ((*cone)->y_min - new_ray.origin.y) / new_ray.direction.y;
	if (within_cone_radius(&new_ray, t.t, (*cone)->y_min) == 1)
	{
		t.cone = *cone;
		t.sphere = NULL;
		t.plan = NULL;
		t.cylinder = NULL;
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
	*cone = (*cone)->next;
}

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
	float			abc[3];
	float			discriminant;
	t_intersection	t;
	t_ray			new_ray;
	float			y0;

	if (!*cone)
		return ;
	new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
	discriminant = get_cone_discriminant(new_ray, abc);
	if (discriminant < 0)
		return ;
	if (fabsf(abc[0]) < EPSILON && fabsf(abc[1]) > EPSILON)
	{
		t.t = -abc[2] / (2 * abc[1]);
		t.cone = *cone;
		t.sphere = NULL;
		t.plan = NULL;
		t.cylinder = NULL;
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, t, *count);
		return ;
	}
	discriminant = sqrt(discriminant);
	t.t = (-abc[1] - discriminant) / (2 * abc[0]);
	t.cone = *cone;
	t.sphere = NULL;
	t.plan = NULL;
	t.cylinder = NULL;
	y0 = new_ray.origin.y + t.t * new_ray.direction.y;
	if (y0 < (*cone)->y_max && y0 > (*cone)->y_min)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
	t.t = (-abc[1] + discriminant) / (2 * abc[0]);
	y0 = new_ray.origin.y + t.t * new_ray.direction.y;
	if (y0 < (*cone)->y_max && y0 > (*cone)->y_min)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, t, *count);
	}
}

t_cone	*ft_cone(void)
{
	t_cone *cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->radius = 1;
	cone->y_max = 1;
	cone->y_min = 0;
	cone->matrix = identity_matrix(4);
	cone->material = ft_material();
	cone->next = NULL;
	return (cone);
}
