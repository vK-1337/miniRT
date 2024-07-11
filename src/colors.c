/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:28:52 by bainur            #+#    #+#             */
/*   Updated: 2024/07/09 11:41:05 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pattern *ft_pattern(t_color *a, t_color *b)
{
	t_pattern *pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->a = a;
	pattern->b = b;
	pattern->transform = identity_matrix(4);
	return (pattern);
}

t_color *ft_stripe_at(t_pattern *pattern, t_tuple point)
{
	if (((int)floor(point.x) + (int)floor(point.y) + (int)floor(point.z)) % 2 == 0)
		return (pattern->a);
	else
		return (pattern->b);
}

t_material *ft_set_pattern(t_comps *comps, int type)
{
	t_tuple *object_point;
	t_tuple *pattern_point;

	object_point = malloc(sizeof(t_tuple));
	pattern_point = malloc(sizeof(t_tuple));
	if (type == SPHERE)
	{
		if (comps->sphere->material->pattern == NULL)
			return (comps->sphere->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point, ft_inversion(comps->sphere->matrix, 4));
		*pattern_point = ft_mult_mat_tuple(object_point, ft_inversion(comps->sphere->material->pattern->transform, 4));
		comps->sphere->material->color = *ft_stripe_at(comps->sphere->material->pattern, *pattern_point);
		return (comps->sphere->material);
	}
	else if (type == PLAN)
	{
		if (comps->plan->material->pattern == NULL)
			return (comps->plan->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point, ft_inversion(comps->plan->matrix, 4));
		*pattern_point = ft_mult_mat_tuple(object_point, ft_inversion(comps->plan->material->pattern->transform, 4));
		comps->plan->material->color = *ft_stripe_at(comps->plan->material->pattern, *pattern_point);
		return (comps->plan->material);
	}
	else if (type == CYLINDER)
	{
		if (comps->cylinder->material->pattern == NULL)
			return (comps->cylinder->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point, ft_inversion(comps->cylinder->matrix, 4));
		*pattern_point = ft_mult_mat_tuple(object_point, ft_inversion(comps->cylinder->material->pattern->transform, 4));
		comps->cylinder->material->color = *ft_stripe_at(comps->cylinder->material->pattern, *pattern_point);
		return (comps->cylinder->material);
	}
	else if (type == CONE)
	{
		if (comps->cone->material->pattern == NULL)
			return (comps->cone->material);
		*object_point = ft_mult_mat_tuple(&comps->over_point, ft_inversion(comps->cone->matrix, 4));
		*pattern_point = ft_mult_mat_tuple(object_point, ft_inversion(comps->cone->material->pattern->transform, 4));
		comps->cone->material->color = *ft_stripe_at(comps->cone->material->pattern, *pattern_point);
		return (comps->cone->material);
	}
	return (NULL);
}
