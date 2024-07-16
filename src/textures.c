/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:01:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/16 16:06:36 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

Image	*load_xpm_image(void *mlx_ptr, const char *file_path)
{
	Image	*image;

	image = malloc(sizeof(Image));
	printf("mlx_ptr = %p\n", mlx_ptr);
	printf("file_path = %s\n", file_path);
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)file_path,
			&image->width, &image->height);
	if (image->img_ptr == NULL)
	{
		printf("Error loading image\n");
		exit(1);
	}
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp,
			&image->size_line, &image->endian);
	return (image);
}

uint8_t	*get_pixel(Image *image, int x, int y)
{
	int	index;

	index = (y * image->size_line) + (x * (image->bpp / 8));
	return ((uint8_t *)&image->data[index]);
}

void	get_interpolated_color(float u, float v, Image *image, t_color *color)
{
	float	x;
	float	y;
	uint8_t	*pixel;

	x = (float)(u * (image->width - 1));
	y = (float)(v * (image->height - 1));
	pixel = get_pixel(image, x, y);
	color->r = pixel[2]; // R
	color->g = pixel[1]; // G
	color->b = pixel[0]; // B
}

void	spherical_mapping(float x, float y, float z, Image *image,
		t_color *color)
{
	float theta = atan2f(z, x);            // Angle autour de l'axe Y
	float phi = acosf(y);                  // Angle du pôle Nord
	float u = (theta + M_PI) / (2 * M_PI); // Remap from [-π, π] to [0, 1]
	float v = phi / M_PI;                  // Remap from [0, π] to [0, 1]
	get_interpolated_color(u, v, image, color);
}

void	planar_mapping(float x, float y, Image *image, t_color *color)
{
	float	u;
	float	v;

	u = fmodf(x + 1.0f, 1.0f);
	v = fmodf(y + 1.0f, 1.0f);
	get_interpolated_color(u, v, image, color);
}

void	cylindrical_mapping(float x, float y, float z, Image *image,
		t_color *color)
{
	float	u;
	float	v;

	u = (atan2f(z, x) / (2 * M_PI)) + 0.5f;
	v = y + 0.5f;
	// Assume y is in the range [-0.5, 0.5]
	get_interpolated_color(u, v, image, color);
}

t_material	*ft_texture(char *path, void *mlx)
{
	t_material *m;

	m = malloc(sizeof(t_material));
	if (!m)
	{
		return (NULL);
	}
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