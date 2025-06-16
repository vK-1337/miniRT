/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:04:20 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 14:58:55 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light	*ft_point_light(t_tuple *position, t_color *intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->position = *position;
	light->intensity = *intensity;
	return (light);
}

void	ft_point_light2(t_light *light, t_tuple position, t_color intensity)
{
	light->position = position;
	light->intensity = intensity;
}

t_material	*ft_material(void)
{
	t_material	*material;

	material = malloc(sizeof(t_material));
	material->color = ft_color_reg(1, 1, 1);
	material->ambiant = 0.5;
	material->ambiant_intensity = 0;
	material->ambiant_color = NULL;
	material->pattern = NULL;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	material->is_texture = 0;
	material->is_pattern = 0;
	material->pattern = NULL;
	material->texture = NULL;
	return (material);
}

t_color	ft_lighting(t_material *m, t_light light, t_comps *comps, void *object)
{
	t_norme_lighting	v;

	ft_lighting_helper2(&v, comps->eyev, comps->normalv);
	if (m->type && m->type != 0 && (m->is_texture || m->is_pattern))
	{
		v.is_textured = 1;
		if (m->is_texture)
			v.eff = define_eff_color(m->type, comps->over_point, object, light);
		else
			v.eff = define_pattern_color(m->type, comps->over_point, object);
	}
	else
		v.eff = ft_mult_color_tog(m->color, light.intensity);
	v.lightv = ft_normalization(ft_dif_tuple(light.position,
				comps->over_point));
	v.ambiant = ft_mult_color(v.eff, m->ambiant);
	v.light_dot_normal = ft_dotproduct(v.lightv, comps->normalv);
	ft_lighting_helper(&v, light, comps->in_shadow, m);
	v.final_color = ft_sum_color(ft_sum_color(ft_sum_color(v.ambiant,
					v.diffuse), v.specular), *m->ambiant_color);
	if (v.is_textured)
		v.final_color.text_color = 1;
	else
		v.final_color.text_color = 0;
	return (v.final_color);
}

void	ft_lighting_helper2(t_norme_lighting *v, t_tuple eyev, t_tuple normalv)
{
	v->eyev = eyev;
	v->normalv = normalv;
	v->is_textured = 0;
}
