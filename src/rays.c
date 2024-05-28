/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:54:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/27 22:01:21 by vk               ###   ########.fr       */
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

t_sphere	ft_sphere(t_tuple center, float radius)
{
	t_sphere	s;
	static int	id;

	s.center = center;
	s.radius = radius;
	s.id = id++;
	return (s);
}

t_discriminant	ft_discriminant(t_ray ray, t_sphere sphere)
{
	t_discriminant	dis;
	t_tuple			sphere_to_ray;

	sphere_to_ray = ft_dif_tuple(ray.origin, sphere.center);
	dis.a = ft_dotproduct(ray.direction, ray.direction);
	dis.b = 2 * ft_dotproduct(ray.direction, sphere_to_ray);
	dis.c = ft_dotproduct(sphere_to_ray, sphere_to_ray) - sphere.radius
		* sphere.radius;
	dis.result = dis.b * dis.b - 4 * dis.a * dis.c;
	return (dis);
}

t_intersection	*ft_intersect(t_ray ray, t_sphere sphere)
{
	t_discriminant	dis;
	float			t1;
	float			t2;

	dis = ft_discriminant(ray, sphere);
	if (dis.result < 0)
		return (0);
	t1 = (-dis.b - sqrt(dis.result)) / (2 * dis.a);
	t2 = (-dis.b + sqrt(dis.result)) / (2 * dis.a);
	return (ft_intersections_tab(2, ft_intersection(t1, sphere),
        ft_intersection(t2, sphere)));
}

t_intersection	ft_intersection(float t, t_sphere sphere)
{
	t_intersection	i;

	i.t = t;
	i.object = sphere;
	return (i);
}

t_intersection	*ft_intersections_tab(int count, ...)
{
	int i;
	va_list args;
	t_intersection *intersections = malloc(sizeof(t_intersection) * count);
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

void	ft_sort_intersections(t_intersection *intersections, int count)
{
    int i;
    int j;
    t_intersection tmp;

    i = 0;
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
            j++;
        }
        i++;
    }
}

t_intersection *ft_hit(t_intersection *intersections, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (intersections[i].t >= 0)
            return (&intersections[i]);
        i++;
    }
    return (NULL);
}

t_ray ray_transform(t_ray ray, float **matrix)
{
  t_ray new_ray;

  new_ray = ft_mult_matrix_tuple(matrix, ray);

  return (new_ray);
}
