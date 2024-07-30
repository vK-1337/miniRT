/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:07:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:08:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	ft_spherical(t_tuple position, t_sphere sphere, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

	point_object = ft_normalization(ft_mult_mat_tuple(&position,
				ft_inversion(sphere.matrix, 4), SECOND));
	spherical_mapping(point_object.x, point_object.y, point_object.z,
		sphere.material->texture, &texture_color);
	return (ft_mult_color_tog(texture_color, light.intensity));
}
