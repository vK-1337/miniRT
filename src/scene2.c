/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:29:30 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 14:48:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	comps->in_shadow = in_shadow;
	if (comps->plan != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, PLAN), *light, comps,
				comps->plan);
	else if (comps->sphere != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, SPHERE), *light, comps,
				comps->sphere);
	else if (comps->cylinder != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, CYLINDER), *light, comps,
				comps->cylinder);
	else if (comps->cone != NULL)
		*tmp_color = ft_lighting(ft_set_pattern(comps, CONE), *light, comps,
				comps->cone);
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
