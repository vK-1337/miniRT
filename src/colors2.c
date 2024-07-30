/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:14:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 18:14:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_material	*set_plan_patt(t_comps *comps, t_norme_set_patt *v)
{
	if (comps->plan->m->pattern == NULL)
		return (free(v->object_point), free(v->pattern_point), comps->plan->m);
	*v->object_point = ft_mult_mat_tuple(&comps->over_point,
			ft_inversion(comps->plan->matrix, 4), SECOND);
	comps->plan->m->color = *ft_stripe_at(comps->plan->m->pattern,
			*v->object_point);
	free(v->pattern_point);
	free(v->object_point);
	return (comps->plan->m);
}

t_material	*set_cone_patt(t_comps *comps, t_norme_set_patt *v)
{
	if (comps->cone->m->pattern == NULL)
		return (free(v->object_point), free(v->pattern_point), comps->cone->m);
	*v->object_point = ft_mult_mat_tuple(&comps->over_point,
			ft_inversion(comps->cone->matrix, 4), SECOND);
	comps->cone->m->color = *ft_stripe_at(comps->cone->m->pattern,
			*v->object_point);
	free(v->pattern_point);
	free(v->object_point);
	return (comps->cone->m);
}

t_material	*set_cylinder_patt(t_comps *comps, t_norme_set_patt *v)
{
	if (comps->cylinder->m->pattern == NULL)
		return (free(v->object_point), free(v->pattern_point),
			comps->cylinder->m);
	*v->object_point = ft_mult_mat_tuple(&comps->over_point,
			ft_inversion(comps->cylinder->matrix, 4), SECOND);
	comps->cylinder->m->color = *ft_stripe_at(comps->cylinder->m->pattern,
			*v->object_point);
	free(v->pattern_point);
	free(v->object_point);
	return (comps->cylinder->m);
}