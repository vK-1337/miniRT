/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:41:54 by udumas            #+#    #+#             */
/*   Updated: 2024/06/05 18:27:57 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersection *ft_add_t(t_intersection *t_tab, t_intersection t[2], int count)
{
	t_intersection *new_t_tab;
	int i;

	i = 0;
	new_t_tab = malloc(sizeof(t_intersection) * (count));
	while (i < count - 2)
	{
		new_t_tab[i] = t_tab[i];
		new_t_tab[i].status = 1;
		i++;
	}
	new_t_tab[i] = t[0];
	new_t_tab[i].status = 1;
	new_t_tab[i + 1] = t[1];
	new_t_tab[i + 1].status = 1;
	free(t_tab);
	return (new_t_tab);
}

void ft_sphere_intersections(t_intersection **t_tab, t_sphere **sphere,
							 t_ray ray, int *count)
{
	t_discriminant dis;
	t_intersection t[2];
	t_ray new_ray;

	if (*sphere == NULL)
		return;
	new_ray = ray_transform(ray, ft_inversion((*sphere)->matrix, 4));
	dis = ft_discriminant(new_ray, *sphere);
	if (dis.result < 0)
	{
		*sphere = (*sphere)->next;
		return;
	}
	t[0].t = (-dis.b - sqrt(dis.result)) / (2 * dis.a);
	t[0].sphere = *sphere;
	t[0].plan = NULL;
	t[1].t = (-dis.b + sqrt(dis.result)) / (2 * dis.a);
	t[1].sphere = *sphere;
	t[1].plan = NULL;
	*count += 2;
	*t_tab = ft_add_t(*t_tab, t, *count);
	*sphere = (*sphere)->next;
}
t_intersection *ft_intersect_world(t_ray ray, t_world **data)
{
	t_intersection *t_tab;
	int count;
	t_sphere *sphere;
	t_plan *plan;

	count = 0;
	if (*data == NULL)
		return (NULL);
	if ((*data)->sphere)
		sphere = *(*data)->sphere;
	else
		sphere = NULL;
	plan = *(*data)->plan;
	t_tab = malloc(sizeof(t_intersection));
	t_tab[0].status = 0;
	while (sphere != NULL || plan != NULL)
	{
		ft_plan_intersect(&t_tab, &plan, ray, &count);
		ft_sphere_intersections(&t_tab, &sphere, ray, &count);
	}
	ft_sort_intersections(t_tab, count);
	return (t_tab);
}

t_comps ft_prepare_computations(t_intersection *i, t_ray ray)
{
	t_comps comps;

	if (i == NULL)
	{
		comps.t = 0;
		comps.sphere = NULL;
		comps.plan = NULL;
		comps.point = *ft_init_tuple(0, 0, 0, 0);
		comps.point = *ft_init_tuple(0, 0, 0, 0);
		comps.eyev = *ft_init_tuple(0, 0, 0, 0);
		comps.normalv = *ft_init_tuple(0, 0, 0, 0);
		comps.over_point = *ft_init_tuple(0, 0, 0, 0);
		comps.inside = 0;
		return (comps);
	}
	comps.t = i[0].t;
	comps.eyev = ft_neg_tuple(ray.direction);
	comps.point = ft_position(ray, comps.t);
	if (i[0].sphere == NULL)
	{
		comps.plan = i[0].plan;
		comps.sphere = NULL;
		comps.type = PLAN;
	}
	else
	{
		comps.sphere = i[0].sphere;
		comps.plan = NULL;
		comps.type = SPHERE;
	}
	comps.normalv = ft_normal_at(comps, comps.point);
	if (ft_dotproduct(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = ft_neg_tuple(comps.normalv);
	}
	else
	{
		comps.inside = 0;
	}
	comps.over_point = ft_sum_tuple(comps.point, ft_mult_vector(comps.normalv,
																EPSILON));
	return (comps);
}

t_color ft_shade_hit(t_world *data, t_comps *comps)
{
	int in_shadow;

	in_shadow = ft_is_shadowed(data, comps->over_point);
	if (comps->sphere == NULL)
	{
		return (ft_lighting(ft_set_pattern(comps, PLAN), *data->light,
							comps->over_point, comps->eyev, comps->normalv, in_shadow));
	}
	else
	{
		return (ft_lighting(ft_set_pattern(comps, SPHERE), *data->light,
							comps->over_point, comps->eyev, comps->normalv, in_shadow));
	}
}

t_color ft_color_at(t_world *data, t_ray ray)
{
	t_intersection *xs;
	t_comps comps;

	xs = ft_intersect_world(ray, &data);
	if (ft_hit(xs, xs[0].count) == NULL)
		return (*ft_color(0, 0, 0));
	comps = ft_prepare_computations(ft_hit(xs, xs[0].count), ray);
	return (ft_shade_hit(data, &comps));
}

float **ft_view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward;
	t_tuple upm;
	t_tuple left;
	t_tuple true_up;
	float **orientation;

	forward = ft_normalization(ft_dif_tuple(to, from));
	upm = ft_normalization(up);
	left = cross_product(forward, upm);
	true_up = cross_product(left, forward);
	orientation = identity_matrix(4);
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = -forward.x;
	orientation[2][1] = -forward.y;
	orientation[2][2] = -forward.z;
	orientation = ft_mult_mat(orientation, translation(-from.x, -from.y,
													   -from.z));
	return (orientation);
}

t_world *ft_default_world(void)
{
	t_world *data;
	t_sphere *s1;
	t_sphere *s2;

	data = malloc(sizeof(t_world));
	data->light = ft_point_light(ft_init_tuple(-10, 10, -10, 1), ft_color(1, 1,
																		  1));
	data->sphere = malloc(sizeof(t_sphere *));
	s1 = ft_sphere();
	s2 = ft_sphere();
	s2->material = ft_material();
	s1->material = ft_material();
	s1->material->color = ft_color(0.8, 1.0, 0.6);
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	s2->matrix = ft_mult_mat(scaling(0.25, 0.25, 0.25), s2->matrix);
	*(data->sphere) = s1;
	s1->next = NULL;
	s2->next = NULL;
	sphere_lstadd_back(data->sphere, s2);
	return (data);
}
