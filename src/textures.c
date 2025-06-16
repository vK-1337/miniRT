/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:01:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 10:10:22 by vda-conc         ###   ########.fr       */
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
