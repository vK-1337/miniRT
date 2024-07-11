/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:26:12 by vk                #+#    #+#             */
/*   Updated: 2024/07/09 14:21:51 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void put_pixel(t_win *win, int x, int y, unsigned int color)
{
    char *dst;

    if ((x > SIZE_X || x < 0) || (y > SIZE_Y || y < 0))
        return;
    dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int exit_window(t_win *win)
{
    // mlx_destroy_image(fractal->mlx, fractal->img);
    mlx_destroy_window(win->mlx, win->win);
    mlx_destroy_display(win->mlx);
    free(win->mlx);
    free(win);
    exit(1);
    return (0);
}

t_win *init_mlx(void)
{
    t_win *win;

    win = malloc(sizeof(t_win));
    win->mlx = mlx_init();
    win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
    win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
    win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
                                  &win->line_length, &win->endian);
    return (win);
}

int main(void)
{
    t_sphere *s1 = ft_sphere();
    t_light *light = ft_point_light(ft_init_tuple(-10, 10, -10, 1), ft_color(1, 1, 1));
    double wall_z = 10;
	double wall_size = 7;
	double canvas_size = 500;
    void *mlx;
    void *win;
    t_material sphere_mat;

    t_tuple ray_origin = *ft_init_tuple(0, 0, -5, 1);
    mlx = mlx_init();
    sphere_mat = *ft_texture("src/461223103.xpm", mlx);
    s1->material = &sphere_mat;
    win = mlx_new_window(mlx, canvas_size, canvas_size, " ");
    double pixel_size = wall_size / canvas_size;
	double half = wall_size / 2;

    t_win data;
    data.mlx = mlx;
    data.win = win;
    data.img = mlx_new_image(mlx, canvas_size, canvas_size);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    int y = 0;

    while (y < canvas_size)
    {
        double world_y = half - pixel_size * y;
        int x = 0;
        while (x < canvas_size)
        {
            double world_x = -half + pixel_size * x;
            t_tuple *position = ft_init_tuple(world_x, world_y, wall_z, 1);
            t_ray r = ft_ray(ray_origin, ft_normalization(ft_dif_tuple(*position, ray_origin)));
            t_intersection *intersections = ft_intersect(r, s1);
            t_intersection *hit = ft_hit(intersections, 2);
            if (hit)
            {
                t_tuple point = ft_position(r, hit->t);
                t_comps comps = ft_prepare_computations(hit, r);
                t_color color = ft_lighting(s1->material, s1, *light, point, ft_neg_tuple(r.direction), ft_normal_at(comps, point), 0, Sphere);
                int color_int = ft_texture_color_to_int(color);
                put_pixel(&data, x, y, color_int);
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx, win, data.img, 0, 0);
    mlx_loop(mlx);
}