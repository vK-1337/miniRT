/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:07:54 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 14:59:10 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	ft_spherical(t_tuple position, t_sphere sphere, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

	point_object = ft_normalization(ft_mult_mat_tuple(&position,
				ft_inversion(sphere.matrix, 4), SECOND));
	spherical_mapping(point_object,
		sphere.m->texture, &texture_color);
	return (ft_mult_color_tog(texture_color, light.intensity));
}

void	ft_lighting_helper(t_norme_lighting *v, t_light light, int in_shadow,
		t_material *m)
{
	if (v->light_dot_normal < 0 || in_shadow)
	{
		color_black(&v->diffuse);
		color_black(&v->specular);
	}
	else
	{
		v->diffuse = ft_mult_color(v->eff, m->diffuse);
		v->diffuse = ft_mult_color(v->diffuse, v->light_dot_normal);
		v->reflectv = ft_reflect(ft_neg_tuple(v->lightv), v->normalv);
		v->reflect_dot_eye = ft_dotproduct(v->reflectv, v->eyev);
		if (v->reflect_dot_eye <= 0)
			color_black(&v->specular);
		else
		{
			v->factor = pow(v->reflect_dot_eye, m->shininess);
			v->specular = ft_mult_color(light.intensity, m->specular);
			v->specular = ft_mult_color(v->specular, v->factor);
		}
	}
}

t_color	define_eff_color(t_objects type, t_tuple position, void *object,
		t_light light)
{
	t_color	effective_color;

	if (type == Sphere)
		effective_color = ft_spherical(position, *(t_sphere *)object, light);
	else if (type == Plan)
		effective_color = ft_planar(position, *(t_plan *)object, light);
	else if (type == Cylinder || type == Cone)
		effective_color = ft_cylindrical(position, *(t_cylinder *)object,
				light);
	else
		effective_color = *(ft_color(1, 1, 1));
	return (effective_color);
}
