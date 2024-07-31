/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:30:46 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 14:34:35 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	*render(void *thread_)
{
	t_render_norme	vars;

	vars.thread = (t_thread *)thread_;
	vars.camera = vars.thread->data->camera;
	vars.win = vars.thread->win;
	vars.data = vars.thread->data;
	vars.y = vars.thread->start_y;
	while (vars.y < vars.thread->end_y)
	{
		vars.x = vars.thread->start_x - 1;
		while (++vars.x < vars.thread->end_x)
		{
			vars.ray = ray_for_pixel(vars.camera, vars.x, vars.y);
			vars.color = ft_color_at(vars.data, vars.ray);
			if (vars.color.text_color == 1)
				vars.color_int = ft_texture_color_to_int(vars.color);
			else
				vars.color_int = color_to_int(vars.color);
			pthread_mutex_lock(vars.data->pixel_put);
			put_pixel(vars.win, vars.x, vars.y, vars.color_int);
			pthread_mutex_unlock(vars.data->pixel_put);
		}
		vars.y++;
	}
	return (NULL);
}

t_camera	*ft_new_camera(float hsize, float vsize, double fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->pixel_size = compute_pixel_size(camera);
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
	t_ray_norme	ray;

	ray.xoffset = (px + 0.5) * camera->pixel_size;
	ray.yoffset = (py + 0.5) * camera->pixel_size;
	ray.world_x = camera->half_width - ray.xoffset;
	ray.world_y = camera->half_height - ray.yoffset;
	ray.tmp_comput = ft_init_tuple(ray.world_x, ray.world_y, -1, 1);
	ray.pixel = ft_mult_mat_tuple(ray.tmp_comput, ft_inversion(camera->matrix,
				4), ALL);
	ray.tmp_comput = ft_init_tuple(0, 0, 0, 1);
	ray.origin = ft_mult_mat_tuple(ray.tmp_comput, ft_inversion(camera->matrix,
				4), ALL);
	ray.direction = ft_normalization(ft_dif_tuple(ray.pixel, ray.origin));
	return (ft_ray(ray.origin, ray.direction));
}
