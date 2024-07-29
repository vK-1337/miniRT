/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:28:52 by bainur            #+#    #+#             */
/*   Updated: 2024/07/29 17:23:34 by vda-conc         ###   ########.fr       */
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

t_color	*ft_checkerboard_at(t_pattern *pattern, float u, float v)
{
	if (((int)floor(u * 10) + (int)floor(v * 10)) % 2 == 0)
		return (pattern->a);
	else
		return (pattern->b);
}

t_material	*ft_set_pattern(t_comps *comps, int type)
{
	t_tuple	*object_point;
	t_tuple	*pattern_point;
	float	theta;
	float	phi;
	float	u;
	float	v;

	object_point = malloc(sizeof(t_tuple));
	pattern_point = malloc(sizeof(t_tuple));
	if (type == SPHERE)
	{
		if (comps->sphere->material->pattern == NULL)
			return (free(object_point), free(pattern_point),
				comps->sphere->material);
		*object_point = ft_normalization(ft_mult_mat_tuple(&comps->over_point,
					ft_inversion(comps->sphere->matrix, 4), SECOND));
		theta = atan2f(object_point->z, object_point->x);
		phi = acosf(object_point->y);
		u = (theta + M_PI) / (2 * M_PI);
		v = phi / M_PI;
		comps->sphere->material->color = *ft_checkerboard_at(comps->sphere->material->pattern,
				u, v);
		free(pattern_point);
		free(object_point);
		return (comps->sphere->material);
	}
	else if (type == PLAN)
	{
		if (comps->plan->material->pattern == NULL)
			return (free(object_point), free(pattern_point),
				comps->plan->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->plan->matrix, 4), SECOND);
		*pattern_point = ft_mult_mat_tuple(object_point,
				ft_inversion(comps->plan->material->pattern->transform, 4),
				SECOND);
		comps->plan->material->color = *ft_stripe_at(comps->plan->material->pattern,
				*pattern_point);
		free(pattern_point);
		free(object_point);
		return (comps->plan->material);
	}
	else if (type == CYLINDER)
	{
		if (comps->cylinder->material->pattern == NULL)
			return (free(object_point), free(pattern_point),
				comps->cylinder->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->cylinder->matrix, 4), SECOND);
		*pattern_point = ft_mult_mat_tuple(object_point,
				ft_inversion(comps->cylinder->material->pattern->transform, 4),
				ALL);
		comps->cylinder->material->color = *ft_stripe_at(comps->cylinder->material->pattern,
				*pattern_point);
		free(pattern_point);
		free(object_point);
		return (comps->cylinder->material);
	}
	else if (type == CONE)
	{
		if (comps->cone->material->pattern == NULL)
			return (free(object_point), free(pattern_point),
				comps->cone->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point,
				ft_inversion(comps->cone->matrix, 4), SECOND);
		*pattern_point = ft_mult_mat_tuple(object_point,
				ft_inversion(comps->cone->material->pattern->transform, 4),
				ALL);
		comps->cone->material->color = *ft_stripe_at(comps->cone->material->pattern,
				*pattern_point);
		free(pattern_point);
		free(object_point);
		return (comps->cone->material);
	}
	return (NULL);
}
