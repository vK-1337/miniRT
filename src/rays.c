/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:54:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/31 10:19:35 by vk               ###   ########.fr       */
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
	static int	id;

	s = malloc(sizeof(t_sphere));
	s->center = *ft_init_tuple(0, 0, 0, 1);
	s->radius = 1;
	s->matrix = identity_matrix(4);
    s->material = ft_material();
	s->id = id++;
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

	t_ray          new_ray;
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
	i.object = sphere;
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

void	ft_sort_intersections(t_intersection *intersections, int count)
{
	int				i;
	int				j;
	t_intersection	tmp;

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
	while (i < count && intersections)
	{
		if (intersections[i].t >= 0)
			return (&intersections[i]);
		i++;
	}
	return (NULL);
}

t_ray	ray_transform(t_ray ray, float **matrix)
{
	t_ray	new_ray;

	new_ray.direction = ft_mult_matrix_tuple(matrix, ray.direction);
	new_ray.origin = ft_mult_matrix_tuple(matrix, ray.origin);
	return (new_ray);
}

t_tuple	ft_mult_matrix_tuple(float **matrix, t_tuple tuple)
{
	t_tuple	new_tuple;

	new_tuple.x = matrix[0][0] * tuple.x + matrix[0][1] * tuple.y + matrix[0][2]
		* tuple.z + matrix[0][3] * tuple.w;
	new_tuple.y = matrix[1][0] * tuple.x + matrix[1][1] * tuple.y + matrix[1][2]
		* tuple.z + matrix[1][3] * tuple.w;
	new_tuple.z = matrix[2][0] * tuple.x + matrix[2][1] * tuple.y + matrix[2][2]
		* tuple.z + matrix[2][3] * tuple.w;
	new_tuple.w = matrix[3][0] * tuple.x + matrix[3][1] * tuple.y + matrix[3][2]
		* tuple.z + matrix[3][3] * tuple.w;
	return (new_tuple);
}
void	set_transform(t_sphere *sphere, float **matrix)
{
	sphere->matrix = matrix;
	return ;
}
