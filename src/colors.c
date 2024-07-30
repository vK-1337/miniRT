/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:28:52 by bainur            #+#    #+#             */
/*   Updated: 2024/07/30 18:15:48 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pattern	*ft_pattern(t_color *a, t_color *b)
{
	t_pattern	*pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->a = a;
	pattern->b = b;
	pattern->transform = identity_matrix(4);
	return (pattern);
}

t_color	*ft_stripe_at(t_pattern *pattern, t_tuple point)
{
	if (((int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z))
		% 2 == 0)
		return (pattern->a);
	else
		return (pattern->b);
}

t_color	*ft_chkr_at(t_pattern *pattern, float u, float v)
{
	if (((int)floor(u * 10) + (int)floor(v * 10)) % 2 == 0)
		return (pattern->a);
	else
		return (pattern->b);
}

t_material	*ft_set_pattern(t_comps *comps, int type)
{
	t_norme_set_patt	v;

	v.object_point = malloc(sizeof(t_tuple));
	if (!v.object_point)
		return (NULL);
	v.pattern_point = malloc(sizeof(t_tuple));
	if (!v.pattern_point)
		return (free(v.object_point), NULL);
	if (type == SPHERE)
		return (set_sphere_patt(comps, &v));
	else if (type == PLAN)
		return (set_plan_patt(comps, &v));
	else if (type == CYLINDER)
		return (set_cylinder_patt(comps, &v));
	else if (type == CONE)
		return (set_cone_patt(comps, &v));
	return (NULL);
}

t_material	*set_sphere_patt(t_comps *comps, t_norme_set_patt *v)
{
	if (comps->sphere->m->pattern == NULL)
		return (free(v->object_point), free(v->pattern_point),
			comps->sphere->m);
	*v->object_point = ft_normalization(ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->sphere->matrix, 4), SECOND));
	v->theta = atan2f(v->object_point->z, v->object_point->x);
	v->phi = acosf(v->object_point->y);
	v->u = (v->theta + M_PI) / (2 * M_PI);
	v->v = v->phi / M_PI;
	comps->sphere->m->color = *ft_chkr_at(comps->sphere->m->pattern, v->u,
			v->v);
	free(v->pattern_point);
	free(v->object_point);
	return (comps->sphere->m);
}
