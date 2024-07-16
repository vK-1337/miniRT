/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:30:46 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/16 16:49:59 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void *render(void *thread_)
{
	t_thread *thread = thread_;
	t_camera *camera = thread->data->camera;
	t_win *win = thread->win;
	t_world *data = thread->data;

	for (int y = thread->start_y; y < thread->end_y; y++)
	{
		for (int x = thread->start_x; x < thread->end_x; x++)
		{
			t_ray ray = ray_for_pixel(camera, x, y);
			t_color color = ft_color_at(data, ray);
			unsigned int color_int = color_to_int(color); // Convert color to int
			pthread_mutex_lock(data->pixel_put);
			put_pixel(win, x, y, color_int);
			pthread_mutex_unlock(data->pixel_put);
		}
	}
	return (NULL);
}

t_camera *ft_new_camera(float hsize, float vsize, double fov)
{
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->pixel_size = compute_pixel_size(camera);
	return (camera);
}

float compute_pixel_size(t_camera *camera)
{
	double half_view;
	double aspect;

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

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
	double xoffset;
	double yoffset;
	double world_x;
	double world_y;
	t_tuple pixel;
	t_tuple origin;
	t_tuple direction;
	t_tuple *tmp_comput;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	tmp_comput = ft_init_tuple(world_x, world_y, -1, 1);
	pixel = ft_mult_mat_tuple(tmp_comput, ft_inversion(camera->matrix, 4), ALL);
	tmp_comput = ft_init_tuple(0, 0, 0, 1);
	origin = ft_mult_mat_tuple(tmp_comput, ft_inversion(camera->matrix, 4), ALL);
	direction = ft_normalization(ft_dif_tuple(pixel, origin));
	return (ft_ray(origin, direction));
}
