/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:51:28 by bainur            #+#    #+#             */
/*   Updated: 2024/06/08 15:49:23 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int within_cone_radius(const t_ray *ray, double t, double cone_val)
{
	double	x;
	double	z;

	x = ray->origin.x + ray->direction.x * t;
	z = ray->origin.z + ray->direction.z * t;
	if ((x * x + z * z) <= (cone_val * cone_val))
		return (1);
	return (0);
}
void ft_check_cone_caps(t_intersection **t_tab, t_cone **cone, t_ray ray, int *count)
{
    t_intersection t;
    
    if (fabsf(ray.direction.y) < EPSILON)
        return ;
    t.t = (*cone)->radius - ray.origin.y / ray.direction.y;
    if (within_cone_radius(&ray, t.t, (*cone)->radius))
    {
        t.cone = *cone;
        t.sphere = NULL;
        t.plan = NULL;
        t.cylinder = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(*t_tab, t, *count);
    }
    t.t = -(*cone)->radius - ray.origin.y / ray.direction.y;
    if (within_cone_radius(&ray, t.t, (*cone)->radius))
    {
        t.cone = *cone;
        t.sphere = NULL;
        t.plan = NULL;
        t.cylinder = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(*t_tab, t, *count);
    }
}

float get_cone_discriminant(t_ray ray, float abc[3], t_cone *cone)
{
    float	discriminant;

	abc[0] = ray.direction.x * ray.direction.x - ray.direction.y * ray.direction.y \
	+ ray.direction.z * ray.direction.z;
	abc[1] = 2 * ray.direction.x * ray.origin.x - 2 * ray.direction.y * ray.origin.y \
		+ 2 * ray.direction.z * ray.origin.z;
	abc[2] = ray.origin.x * ray.origin.x - ray.origin.y * ray.origin.y \
		+ ray.origin.z * ray.origin.z;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	return (discriminant);
}
void	ft_cone_intersect(t_intersection **t_tab, t_cone **cone, t_ray ray,
		int *count)
{
	float abc[3];
    float discriminant;
    t_intersection t;
    t_ray new_ray;

    if (*cone == NULL)
        return ;
    new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
    ft_check_cone_caps(t_tab, cone, new_ray, count);
    discriminant = get_cone_discriminant(new_ray, abc);
    printf("discriminant = %f\n", discriminant);
    if (discriminant < 0)
    {
        *cone = (*cone)->next;
        return ;
    }
    if (fabsf(abc[0]) < EPSILON && fabsf(abc[1]) > 0.1)
    {
        t.t = -abc[2] / (2 * abc[1]);
        t.cone = *cone;
        t.sphere = NULL;
        t.plan = NULL;
        t.cylinder = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(*t_tab, t, *count);
        *cone = (*cone)->next;
        return ;
    }
    discriminant = sqrt(discriminant);
    t.t = (-abc[1] - discriminant) / (2*abc[0]);
    t.cone = *cone;
    t.sphere = NULL;
    t.plan = NULL;
    t.cylinder = NULL;
    *count += 1;
    *t_tab = ft_add_one_t(*t_tab, t, *count);
    t.t = (-abc[1] + discriminant) / (2*abc[0]);
    *count += 1;
    *t_tab = ft_add_one_t(*t_tab, t, *count);
    *cone = (*cone)->next;
}

t_cone	*ft_cone(void)
{
	t_cone *cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->radius = 1;
	cone->matrix = identity_matrix(4);
	cone->material = ft_material();
	cone->next = NULL;
	return (cone);
}