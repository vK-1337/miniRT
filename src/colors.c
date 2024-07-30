/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:28:52 by bainur            #+#    #+#             */
/*   Updated: 2024/07/30 17:41:42 by vda-conc         ###   ########.fr       */
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
	v.pattern_point = malloc(sizeof(t_tuple));
	if (type == SPHERE)
	{
		if (comps->sphere->m->pattern == NULL)
			return (free(v.object_point), free(v.pattern_point),
				comps->sphere->m);
		*v.object_point = ft_normalization(ft_mult_mat_tuple(&comps->over_point,
					ft_inversion(comps->sphere->matrix, 4), SECOND));
		v.theta = atan2f(v.object_point->z, v.object_point->x);
		v.phi = acosf(v.object_point->y);
		v.u = (v.theta + M_PI) / (2 * M_PI);
		v.v = v.phi / M_PI;
		comps->sphere->m->color = *ft_chkr_at(comps->sphere->m->pattern,
				v.u, v.v);
		free(v.pattern_point);
		free(v.object_point);
		return (comps->sphere->m);
	}
	else if (type == PLAN)
	{
		if (comps->plan->material->pattern == NULL)
			return (free(v.object_point), free(v.pattern_point),
				comps->plan->material);
		*v.object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->plan->matrix, 4), SECOND);
		*v.pattern_point = ft_mult_mat_tuple(v.object_point,
				ft_inversion(comps->plan->material->pattern->transform, 4),
				SECOND);
		comps->plan->material->color = *ft_stripe_at(comps->plan->material->pattern,
				*v.pattern_point);
		free(v.pattern_point);
		free(v.object_point);
		return (comps->plan->material);
	}
	else if (type == CYLINDER)
	{
		if (comps->cylinder->m->pattern == NULL)
			return (free(v.object_point), free(v.pattern_point),
				comps->cylinder->m);
		*v.object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->cylinder->matrix, 4), SECOND);
		*v.pattern_point = ft_mult_mat_tuple(v.object_point,
				ft_inversion(comps->cylinder->m->pattern->transform, 4),
				ALL);
		comps->cylinder->m->color = *ft_stripe_at(comps->cylinder->m->pattern,
				*v.pattern_point);
		free(v.pattern_point);
		free(v.object_point);
		return (comps->cylinder->m);
	}
	else if (type == CONE)
	{
		if (comps->cone->material->pattern == NULL)
			return (free(v.object_point), free(v.pattern_point),
				comps->cone->material);
		*v.object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->cone->matrix, 4), SECOND);
		*v.pattern_point = ft_mult_mat_tuple(v.object_point,
				ft_inversion(comps->cone->material->pattern->transform, 4),
				ALL);
		comps->cone->material->color = *ft_stripe_at(comps->cone->material->pattern,
				*v.pattern_point);
		free(v.pattern_point);
		free(v.object_point);
		return (comps->cone->material);
	}
	return (NULL);
}
