/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:41:54 by udumas            #+#    #+#             */
/*   Updated: 2024/07/31 13:24:28 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersection	*ft_add_t(t_intersection **t_tab, t_intersection t[2],
		int count)
{
	t_intersection	*new_t_tab;
	int				i;

	i = 0;
	new_t_tab = calloc(count, sizeof(t_intersection));
	if (!new_t_tab)
		return (NULL);
	while (i < count - 2)
	{
		new_t_tab[i] = (*t_tab)[i];
		new_t_tab[i].status = 1;
		i++;
	}
	new_t_tab[i] = t[0];
	new_t_tab[i].status = 1;
	new_t_tab[i + 1] = t[1];
	new_t_tab[i + 1].status = 1;
	free(*t_tab);
	return (new_t_tab);
}

void	ft_sphere_intersections(t_intersection **t_tab, t_sphere **sphere,
		t_ray ray, int *count)
{
	t_discriminant	dis;
	t_intersection	t[2];
	t_ray			new_ray;

	if (*sphere == NULL)
		return ;
	new_ray = ray_transform(ray, ft_inversion((*sphere)->matrix, 4));
	dis = ft_discriminant(new_ray, *sphere);
	if (dis.result < 0)
	{
		*sphere = (*sphere)->next;
		return ;
	}
	t[0].t = (-dis.b - sqrt(dis.result)) / (2 * dis.a);
	t[0].sphere = *sphere;
	t[0].plan = NULL;
	t[0].cylinder = NULL;
	t[0].cone = NULL;
	t[1].t = (-dis.b + sqrt(dis.result)) / (2 * dis.a);
	t[1].sphere = *sphere;
	t[1].plan = NULL;
	t[1].cylinder = NULL;
	t[1].cone = NULL;
	*count += 2;
	*t_tab = ft_add_t(t_tab, t, *count);
	*sphere = (*sphere)->next;
}

t_intersection	*ft_intersect_world(t_ray ray, t_world **data)
{
	t_norme_intersect_world	v;

	if (!prepare_all_data(&v))
		return (NULL);
	if (*data == NULL)
		return (NULL);
	if ((*data)->sphere)
		v.sphere = *(*data)->sphere;
	if ((*data)->plan)
		v.plan = *(*data)->plan;
	if ((*data)->cylinder)
		v.cylinder = *(*data)->cylinder;
	if ((*data)->cone)
		v.cone = *(*data)->cone;
	while (v.sphere != NULL || v.plan != NULL || v.cylinder != NULL
		|| v.cone != NULL)
	{
		ft_plan_intersect(&v.t_tab, &v.plan, ray, &v.count);
		ft_sphere_intersections(&v.t_tab, &v.sphere, ray, &v.count);
		ft_cylinder_intersect(&v.t_tab, &v.cylinder, ray, &v.count);
		ft_cylinder_caps_intersect(&v.t_tab, &v.cylinder, ray, &v.count);
		ft_cone_intersect(&v.t_tab, &v.cone, ray, &v.count);
		ft_check_cone_caps(&v.t_tab, &v.cone, ray, &v.count);
	}
	return (ft_sort_intersections(v.t_tab, v.count), v.t_tab);
}

int	prepare_all_data(t_norme_intersect_world *v)
{
	v->sphere = NULL;
	v->plan = NULL;
	v->cylinder = NULL;
	v->cone = NULL;
	v->t_tab = NULL;
	v->count = 0;
	v->t_tab = calloc(1, sizeof(t_intersection));
	if (!v->t_tab)
		return (0);
	v->t_tab[0].status = 0;
	return (1);
}

t_comps	ft_prepare_computations(t_intersection *i, t_ray ray)
{
	t_comps	comps;

	if (i == NULL)
		return (ft_null_comps());
	comps.t = i[0].t;
	comps.eyev = ft_neg_tuple(ray.direction);
	comps.point = ft_position(ray, comps.t);
	if (i[0].sphere != NULL)
		ft_sphere_comps(&comps, i[0].sphere);
	else if (i[0].plan != NULL)
		ft_plan_comps(&comps, i[0].plan);
	else if (i[0].cylinder != NULL)
		ft_cylinder_comps(&comps, i[0].cylinder);
	else if (i[0].cone != NULL)
		ft_cone_comps(&comps, i[0].cone);
	comps.normalv = ft_normal_at(comps, comps.point);
	comps.inside = 0;
	if (ft_dotproduct(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = ft_neg_tuple(comps.normalv);
	}
	comps.over_point = ft_sum_tuple(comps.point, ft_mult_vector(comps.normalv,
				EPSILON));
	return (comps);
}

t_comps	ft_null_comps(void)
{
	t_comps	comps;

	comps.t = 0;
	comps.sphere = NULL;
	comps.plan = NULL;
	comps.point = (t_tuple){0, 0, 0, 0};
	comps.eyev = (t_tuple){0, 0, 0, 0};
	comps.normalv = (t_tuple){0, 0, 0, 0};
	comps.over_point = (t_tuple){0, 0, 0, 0};
	comps.inside = 0;
	return (comps);
}

void	ft_sphere_comps(t_comps *comps, t_sphere *sphere)
{
	comps->sphere = sphere;
	comps->plan = NULL;
	comps->cylinder = NULL;
	comps->cone = NULL;
	comps->type = SPHERE;
}

void	ft_plan_comps(t_comps *comps, t_plan *plan)
{
	comps->plan = plan;
	comps->sphere = NULL;
	comps->cylinder = NULL;
	comps->cone = NULL;
	comps->type = PLAN;
}

void	ft_cylinder_comps(t_comps *comps, t_cylinder *cylinder)
{
	comps->cylinder = cylinder;
	comps->sphere = NULL;
	comps->plan = NULL;
	comps->cone = NULL;
	comps->type = CYLINDER;
}

void	ft_cone_comps(t_comps *comps, t_cone *cone)
{
	comps->cone = cone;
	comps->sphere = NULL;
	comps->plan = NULL;
	comps->cylinder = NULL;
	comps->type = CONE;
}

t_color	ft_shade_hit(t_world *data, t_comps *comps)
{
	int		in_shadow;
	t_color	color;
	t_color	*tmp_color;
	t_light	*light;

	light = *data->light;
	color = ft_color_reg(0, 0, 0);
	while (light != NULL)
	{
		tmp_color = malloc(sizeof(t_color));
		if (!tmp_color)
			return (color);
		in_shadow = ft_is_shadowed(data, comps->over_point);
		define_tmp_color(tmp_color, comps, light, in_shadow);
		color = ft_sum_color(color, *tmp_color);
		if (tmp_color->text_color == 1)
			color.text_color = 1;
		else
			color.text_color = 0;
		free(tmp_color);
		light = light->next;
	}
	return (color);
}

void	define_tmp_color(t_color *tmp_color, t_comps *comps, t_light *light,
		int in_shadow)
{
	if (comps->plan != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, PLAN), *light,
				comps->over_point, comps->eyev, comps->normalv, in_shadow,
				comps->plan, Plan);
	else if (comps->sphere != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, SPHERE), *light,
				comps->point, comps->eyev, comps->normalv, in_shadow,
				comps->sphere, Sphere);
	else if (comps->cylinder != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, CYLINDER), *light,
				comps->over_point, comps->eyev, comps->normalv, in_shadow,
				comps->cylinder, Cylinder);
	else if (comps->cone != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, CONE), *light,
				comps->over_point, comps->eyev, comps->normalv, in_shadow,
				comps->cone, Cone);
	else
		tmp_color = ft_color(0, 0, 0);
}

t_color	ft_color_at(t_world *data, t_ray ray)
{
	t_intersection	*xs;
	t_comps			comps;

	xs = ft_intersect_world(ray, &data);
	if (ft_hit(xs, xs[0].count) == NULL)
		return (free(xs), ft_color_reg(0, 0, 0));
	comps = ft_prepare_computations(ft_hit(xs, xs[0].count), ray);
	free(xs);
	return (ft_shade_hit(data, &comps));
}

float	**ft_view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	upm;
	t_tuple	left;
	t_tuple	true_up;
	float	**orientation;

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
				-from.z), ALL);
	return (orientation);
}
