/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:30:46 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/15 15:22:02 by vda-conc         ###   ########.fr       */
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
            // ! IF COLOR IS TEXTURE COLOR THEN USE THE TEXTURE COLOR INT FUNCTION
			// unsigned int color_int = color_to_int(color); // Convert color to int
            unsigned int color_int_texture = ft_texture_color_to_int(color);
			pthread_mutex_lock(data->pixel_put);
			put_pixel(win, x, y, color_int_texture);
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
	camera->matrix = identity_matrix(4);
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

	// printf("px: %d py: %d\n", px, py);
	// printf("camera->pixel_size: %f\n", camera->pixel_size);
	// printf("camera->half_width: %f\n", camera->half_width);
	// printf("camera->half_height: %f\n", camera->half_height);
	// print_matrix(camera->matrix, 4);
	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	tmp_comput = ft_init_tuple(world_x, world_y, -1, 1);
	pixel = ft_mult_mat_tuple(tmp_comput, ft_inversion(camera->matrix, 4));
	free(tmp_comput);
	tmp_comput = ft_init_tuple(0, 0, 0, 1);
	origin = ft_mult_mat_tuple(tmp_comput, ft_inversion(camera->matrix, 4));
	free(tmp_comput);
	direction = ft_normalization(ft_dif_tuple(pixel, origin));
	// printf("origin: %f %f %f\n", origin.x, origin.y, origin.z);
	// printf("direction: %f %f %f\n", direction.x, direction.y, direction.z);
	// printf("\n");
	return (ft_ray(origin, direction));
}
