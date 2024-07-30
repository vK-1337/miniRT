/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:07:14 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:09:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	ft_planar(t_tuple position, t_plan plan, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;
	float	plane_width;
	float	plane_height;

	calculate_plane_dimensions(plan.matrix, &plane_width, &plane_height);
	point_object = ft_mult_mat_tuple(&position, ft_inversion(plan.matrix, 4),
			SECOND);
	planar_mapping(point_object.x, point_object.z, plan.material->texture,
		&texture_color, plane_width, plane_height);
	return (ft_mult_color_tog(texture_color, light.intensity));
}

t_color	ft_cylindrical(t_tuple position, t_cylinder cylinder, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

	point_object = ft_normalization(ft_mult_mat_tuple(&position,
				ft_inversion(cylinder.matrix, 4), SECOND));
	cylindrical_mapping(point_object.x, point_object.y, point_object.z,
		cylinder.material->texture, &texture_color);
	return (ft_mult_color_tog(texture_color, light.intensity));
}

unsigned int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	if (color.r > 1)
		color.r = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.b > 1)
		color.b = 1;
	r = (unsigned int)(color.r * 255);
	g = (unsigned int)(color.g * 255);
	b = (unsigned int)(color.b * 255);
	return ((r << 16) | (g << 8) | b);
}

int	ft_texture_color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r);
	g = (int)(color.g);
	b = (int)(color.b);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

void	color_black(t_color *color)
{
	color->r = 0.0;
	color->g = 0.0;
	color->b = 0.0;
	return ;
}
