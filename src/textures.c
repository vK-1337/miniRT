/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:01:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 10:05:50 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_image	*load_xpm_image(void *mlx_ptr, const char *file_path)
{
	t_image	*image;
	char	*trimmed_path;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	trimmed_path = ft_strtrim((char *)file_path, "\n");
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, trimmed_path, &image->width,
			&image->height);
	free(trimmed_path);
	if (image->img_ptr == NULL)
		return (printf("Error loading image.\n"), free(image), NULL);
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (image);
}

uint8_t	*get_pixel(t_image *image, int x, int y)
{
	int	index;

	index = (y * image->size_line) + (x * (image->bpp / 8));
	return ((uint8_t *)&image->data[index]);
}

void	get_interpolated_color(float u, float v, t_image *image, t_color *color)
{
	float	x;
	float	y;
	uint8_t	*pixel;

	x = (float)(u * (image->width - 1));
	y = (float)(v * (image->height - 1));
	pixel = get_pixel(image, x, y);
	color->r = pixel[2];
	color->g = pixel[1];
	color->b = pixel[0];
}

void	spherical_mapping(t_tuple point, t_image *image, t_color *color)
{
	float	theta;
	float	phi;
	float	u;
	float	v;

	theta = atan2f(point.z, point.x);
	phi = acosf(point.y);
	u = (theta + M_PI) / (2 * M_PI);
	v = phi / M_PI;
	get_interpolated_color(u, v, image, color);
}

float	distance(t_tuple a, t_tuple b)
{
	return (sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z
				- a.z) * (b.z - a.z)));
}

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
