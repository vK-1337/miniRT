/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:37:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/25 14:09:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	define_pattern_color(t_objects type, t_tuple position, void *object, t_light light)
{
	t_color	effective_color;
    (void)light;

	if (type == Sphere)
    {
        t_tuple object_point = ft_normalization(ft_mult_mat_tuple(&position, ft_inversion(((t_sphere *)object)->matrix, 4), SECOND));
        float theta = atan2f(object_point.z, object_point.x);
        float phi = acosf(object_point.y);
        float u = (theta + M_PI) / (2 * M_PI);
        float v = phi / M_PI;
        effective_color = *ft_checkerboard_at(((t_sphere *)object)->material->pattern, u, v);
    }
    else if (type == Plan)
    {
        float plane_width;
        float plane_height;
        calculate_plane_dimensions(((t_plan *)object)->matrix, &plane_width, &plane_height);
	    t_tuple point_object = ft_mult_mat_tuple(&position, ft_inversion(((t_plan *)object)->matrix, 4), SECOND);
        // float scale_u = 1.0f;
        // float u = point_object.x / (plane_width * scale_u);
        // float v = point_object.y / (plane_height * scale_u);
        effective_color = *ft_stripe_at(((t_plan *)object)->material->pattern, point_object);
    }
	else if (type == Cylinder || type == Cone)
		effective_color = ((t_cylinder *)object)->material->color;
	else
		effective_color = *(ft_color(1, 1, 1));
	return (effective_color);
}