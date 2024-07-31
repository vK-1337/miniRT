/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:41:54 by udumas            #+#    #+#             */
/*   Updated: 2024/07/31 13:30:44 by vda-conc         ###   ########.fr       */
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
	t_norme_sphere_intersect	v;

	if (*sphere == NULL)
		return ;
	v.new_ray = ray_transform(ray, ft_inversion((*sphere)->matrix, 4));
	v.dis = ft_discriminant(v.new_ray, *sphere);
	if (v.dis.result < 0)
	{
		*sphere = (*sphere)->next;
		return ;
	}
	v.t[0].t = (-v.dis.b - sqrt(v.dis.result)) / (2 * v.dis.a);
	v.t[0].sphere = *sphere;
	v.t[0].plan = NULL;
	v.t[0].cylinder = NULL;
	v.t[0].cone = NULL;
	v.t[1].t = (-v.dis.b + sqrt(v.dis.result)) / (2 * v.dis.a);
	v.t[1].sphere = *sphere;
	v.t[1].plan = NULL;
	v.t[1].cylinder = NULL;
	v.t[1].cone = NULL;
	*count += 2;
	*t_tab = ft_add_t(t_tab, v.t, *count);
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
