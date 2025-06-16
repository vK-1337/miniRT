/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:09:59 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 11:02:47 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	calculate_plane_dimensions(float **matrix, float *width, float *height)
{
	t_tuple	transformed_corners[4];
	t_tuple	corners[4];
	int		i;

	initialize_corners(corners);
	i = 0;
	while (i < 4)
	{
		transformed_corners[i] = ft_mult_matrix_tuple(matrix, &corners[i],
				NONE);
		i++;
	}
	*width = distance(transformed_corners[0], transformed_corners[1]);
	*height = distance(transformed_corners[1], transformed_corners[2]);
}

void	initialize_corners(t_tuple corners[4])
{
	corners[0] = (t_tuple){-1, 0, -1, 1};
	corners[1] = (t_tuple){1, 0, -1, 1};
	corners[2] = (t_tuple){1, 0, 1, 1};
	corners[3] = (t_tuple){-1, 0, 1, 1};
}

void	planar_mapping(t_tuple point_object, t_image *image, t_color *color,
		t_norme_planar_mapping v_i)
{
	float	scale_u;
	float	u;
	float	v;

	scale_u = 140.0f;
	u = point_object.x / (v_i.plane_width * scale_u);
	v = point_object.z / (v_i.plane_height * scale_u);
	u = fmodf(u, 1.0f);
	v = fmodf(v, 1.0f);
	if (u < 0)
		u += 1.0f;
	if (v < 0)
		v += 1.0f;
	get_interpolated_color(u, v, image, color);
}

void	cylindrical_mapping(t_tuple point_object, t_image *image,
		t_color *color)
{
	float	u;
	float	v;

	u = (atan2f(point_object.z, point_object.x) / (2 * M_PI)) + 0.5f;
	v = point_object.y + 0.5f;
	get_interpolated_color(u, v, image, color);
}

t_material	*ft_texture(char *path, void *mlx)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->color = ft_color_reg(1, 1, 1);
	m->ambiant = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200;
	m->is_texture = 1;
	m->pattern = NULL;
	m->texture = load_xpm_image(mlx, path);
	return (m);
}
