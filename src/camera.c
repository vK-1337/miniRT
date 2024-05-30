/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:30:46 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/30 17:13:57 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera	ft_new_camera(float hsize, float vsize, double fov)
{
	t_camera	camera;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = fov;
	camera.matrix = identity_matrix(4);
	camera.pixel_size = compute_pixel_size(&camera);
	return (camera);
}

float	compute_pixel_size(t_camera *camera)
{
	double	half_view;
	double	aspect;

	half_view = tan(camera->fov / 2);
	aspect = camera->hsize / camera->vsize;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	return ((camera->half_width * 2) / camera->hsize);
}

t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;
	t_tuple	tmp_comput;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	tmp_comput = ft_init_tuple(world_x, world_y, -1, 1);
	pixel = ft_mult_mat_tuple(&tmp_comput, ft_inversion(camera->matrix, 4));
	tmp_comput = ft_init_tuple(0, 0, 0, 1);
	origin = ft_mult_mat_tuple(&tmp_comput, ft_inversion(camera->matrix, 4));
	direction = ft_normalization(ft_dif_tuple(pixel, origin));
	return (ft_ray(origin, direction));
}


