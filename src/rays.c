/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:54:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/29 18:38:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	ft_ray(t_tuple origin, t_tuple direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

t_tuple	ft_position(t_ray r, float t)
{
	t_tuple	position;

	position = ft_sum_tuple(r.origin, ft_mult_vector(r.direction, t));
	return (position);
}

t_sphere	*ft_sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->center = *ft_init_tuple(0, 0, 0, 1);
	s->radius = 1;
	s->matrix = identity_matrix(4);
	s->material = ft_material();
	return (s);
}

t_discriminant	ft_discriminant(t_ray ray, t_sphere *sphere)
{
	t_discriminant	dis;
	t_tuple			sphere_to_ray;

	sphere_to_ray = ft_dif_tuple(ray.origin, sphere->center);
	dis.a = ft_dotproduct(ray.direction, ray.direction);
	dis.b = 2 * ft_dotproduct(ray.direction, sphere_to_ray);
	dis.c = ft_dotproduct(sphere_to_ray, sphere_to_ray) - sphere->radius
		* sphere->radius;
	dis.result = (dis.b * dis.b) - 4 * dis.a * dis.c;
	return (dis);
}

t_intersection	*ft_intersect(t_ray ray, t_sphere *sphere)
{
	t_discriminant	dis;
	float			t1;
	float			t2;
	t_ray			new_ray;

	new_ray = ray_transform(ray, ft_inversion(sphere->matrix, 4));
	dis = ft_discriminant(new_ray, sphere);
	if (dis.result < 0)
		return (0);
	t1 = (-dis.b - sqrt(dis.result)) / (2 * dis.a);
	t2 = (-dis.b + sqrt(dis.result)) / (2 * dis.a);
	return (ft_intersections_tab(2, ft_intersection(t1, sphere),
			ft_intersection(t2, sphere)));
}

t_intersection	ft_intersection(float t, t_sphere *sphere)
{
	t_intersection	i;

	i.t = t;
	i.sphere = sphere;
	return (i);
}

t_intersection	*ft_intersections_tab(int count, ...)
{
	int				i;
	va_list			args;
	t_intersection	*intersections;

	intersections = malloc(sizeof(t_intersection) * count);
	if (!intersections)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		intersections[i] = va_arg(args, t_intersection);
		i++;
	}
	ft_sort_intersections(intersections, count);
	va_end(args);
	return (intersections);
}
