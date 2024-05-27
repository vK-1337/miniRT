/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:54:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/27 14:30:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray ft_ray(t_tuple origin, t_tuple direction)
{
    t_ray	r;

    r.origin = origin;
    r.direction = direction;
    return (r);
}

t_tuple ft_position(t_ray r, float t)
{
    t_tuple	position;

    position = ft_sum_tuple(r.origin, ft_mult_vector(r.direction, t));
    return (position);
}

t_sphere ft_sphere(t_tuple center, float radius)
{
    t_sphere	s;
    static int id;

    s.center = center;
    s.radius = radius;
    s.id = id++;
    return (s);
}

t_discriminant ft_discriminant(t_ray ray, t_sphere sphere)
{
    t_discriminant dis;
    t_tuple sphere_to_ray;

    sphere_to_ray = ft_dif_tuple(ray.origin, sphere.center);
    dis.a = ft_dot(ray.direction, ray.direction);
    dis.b = 2 * ft_dot(ray.direction, sphere_to_ray);
    dis.c = ft_dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;

    dis.result = dis.b * dis.b - 4 * dis.a * dis.c;
    return (dis);
}

int ft_intersect(t_ray ray, t_sphere sphere, float *t1, float *t2)
{
    t_discriminant dis;
    float t1;
    float t2;

    dis = ft_discriminant(ray, sphere);
    if (dis.result < 0)
        return (0);
    *t1 = (-dis.b - sqrt(dis.result)) / (2 * dis.a);
    *t2 = (-dis.b + sqrt(dis.result)) / (2 * dis.a);
    return (1);
}

t_intersection ft_intersection(float t, t_sphere sphere)
{
    t_intersection i;

    i.t = t;
    i.object = sphere;
    return (i);
}

t_intersection *ft_intersections_tab()
