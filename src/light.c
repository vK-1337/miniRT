/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:04:20 by vda-conc          #+#    #+#             */
/*   Updated: 2024/06/15 17:03:20 by bainur           ###   ########.fr       */
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
	t_color		*color;

	color = malloc(sizeof(t_color));
	color->r = 1;
	color->g = 1;
	color->b = 1;
	material = malloc(sizeof(t_material));
	material->color = color;
	material->ambiant_color = malloc(sizeof(t_color));
	(*material->ambiant_color) = ft_mult_color((t_color){1,1,1}, 0.1);
	material->pattern = NULL;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	return (material);
}

t_color	ft_lighting(t_material *m, t_light light, t_tuple position,
		t_tuple eyev, t_tuple normalv, int in_shadow)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_color	diffuse;
	t_color	specular;
	t_tuple	reflectv;
	t_color	ambiant;
	float	factor;
	float	reflect_dot_eye;
	float	light_dot_normal;

	effective_color = ft_mult_color_tog(*m->color, light.colors);
	lightv = ft_normalization(ft_dif_tuple(light.position, position));
	ambiant = ft_mult_color_tog(effective_color, *m->ambiant_color);
	light_dot_normal = ft_dotproduct(lightv, normalv);
	if (light_dot_normal < 0 || in_shadow)
	{
		color_black(&diffuse);
		color_black(&specular);
	}
	else
	{
		diffuse = ft_mult_color(effective_color, m->diffuse);
		diffuse = ft_mult_color(diffuse, light_dot_normal);
		reflectv = ft_reflect(ft_neg_tuple(lightv), normalv);
		reflect_dot_eye = ft_dotproduct(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			color_black(&specular);
		else
		{
			factor = pow(reflect_dot_eye, m->shininess);
			specular = ft_mult_color(light.colors, m->specular);
			specular = ft_mult_color(specular, factor);
		}
		printf("diffuse: %f %f %f\n", diffuse.r, diffuse.g, diffuse.b);
		printf("specular: %f %f %f\n", specular.r, specular.g, specular.b);
		printf("ambiant: %f %f %f\n", ambiant.r, ambiant.g, ambiant.b);
	}
	return (ft_sum_color(ft_sum_color(ambiant, diffuse), specular));
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

void	color_black(t_color *color)
{
	color->r = 0.0;
	color->g = 0.0;
	color->b = 0.0;
	return ;
}
