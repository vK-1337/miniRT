/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:04:20 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/19 22:20:52 by vda-conc         ###   ########.fr       */
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
	material->pattern = NULL;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200;
	material->is_texture = 0;
	material->pattern = NULL;
	material->texture = NULL;
	return (material);
}

t_color	ft_lighting(t_material *m, t_light light, t_tuple position,
		t_tuple eyev, t_tuple normalv, int in_shadow, void *object,
		t_objects type)
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
	int		is_textured;
	t_color	final_color;

	if (type && type != 0 && m->is_texture)
	{
        if (type == Plan)
        {
            printf("Plan position in FT_LIGHTING x = %f, y = %f, z = %f\n", position.x, position.y, position.z);
        }
		is_textured = 1;
		effective_color = define_effective_color(type, position, object, light);
	}
	else
	{
		is_textured = 0;
		effective_color = ft_mult_color_tog(m->color, light.intensity);
	}
	lightv = ft_normalization(ft_dif_tuple(light.position, position));
	ambiant = ft_mult_color(effective_color, m->ambiant);
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
			specular = ft_mult_color(light.intensity, m->specular);
			specular = ft_mult_color(specular, factor);
		}
	}
	final_color = ft_sum_color(ft_sum_color(ft_sum_color(ambiant, diffuse),
				specular), *m->ambiant_color);
	if (is_textured)
	{
		final_color.text_color = 1;
	}
	else
	{
		final_color.text_color = 0;
	}
	return (final_color);
}

t_color	define_effective_color(t_objects type, t_tuple position, void *object,
		t_light light)
{
	t_color	effective_color;

	if (type == Sphere)
		effective_color = ft_spherical(position, *(t_sphere *)object, light);
	else if (type == Plan)
    {
        printf("x = %f, y = %f, z = %f\n", position.x, position.y, position.z);
		effective_color = ft_planar(position, *(t_plan *)object, light);
    }
	else if (type == Cylinder || type == Cone)
		effective_color = ft_cylindrical(position, *(t_cylinder *)object,
				light);
	else
		effective_color = *(ft_color(1, 1, 1));
	return (effective_color);
}

t_color	ft_spherical(t_tuple position, t_sphere sphere, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

	point_object = ft_normalization(ft_mult_mat_tuple(&position, ft_inversion(sphere.matrix, 4),
			SECOND));
	spherical_mapping(point_object.x, point_object.y, point_object.z,
		sphere.material->texture, &texture_color);
	return (ft_mult_color_tog(texture_color, light.intensity));
}

t_color	ft_planar(t_tuple position, t_plan plan, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

    printf("position.x = %f, position.y = %f, position.z = %f\n", position.x, position.y, position.z);
	point_object = ft_normalization(ft_mult_mat_tuple(&position, ft_inversion(plan.matrix, 4),
			SECOND));
	planar_mapping(point_object.x, point_object.y, plan.material->texture,
		&texture_color);
	return (ft_mult_color_tog(texture_color, light.intensity));
}

t_color	ft_cylindrical(t_tuple position, t_cylinder cylinder, t_light light)
{
	t_tuple	point_object;
	t_color	texture_color;

	point_object = ft_normalization(ft_mult_mat_tuple(&position, ft_inversion(cylinder.matrix,
				4), SECOND));
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
