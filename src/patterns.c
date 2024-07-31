/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:37:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 17:48:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	define_pattern_color(t_objects type, t_tuple position, void *object)
{
	t_define_patt_norme	vars;

	if (type == Sphere)
	{
		vars.object_point = ft_normalization(ft_mult_mat_tuple(&position,
					ft_inversion(((t_sphere *)object)->matrix, 4), SECOND));
		vars.theta = atan2f(vars.object_point.z, vars.object_point.x);
		vars.phi = acosf(vars.object_point.y);
		vars.u = (vars.theta + M_PI) / (2 * M_PI);
		vars.v = vars.phi / M_PI;
		vars.eff_color = *ft_chkr_at(((t_sphere *)object)->m->pattern,
				vars.u, vars.v);
	}
	else if (type == Plan)
	{
		vars.point_object = ft_mult_mat_tuple(&position,
				ft_inversion(((t_plan *)object)->matrix, 4), SECOND);
		vars.eff_color = *ft_stripe_at(((t_plan *)object)->m->pattern,
				vars.point_object);
	}
	else if (type == Cylinder || type == Cone)
		vars.eff_color = ((t_cylinder *)object)->m->color;
	else
		vars.eff_color = *(ft_color(1, 1, 1));
	return (vars.eff_color);
}
