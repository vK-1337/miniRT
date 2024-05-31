/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:26:12 by vk                #+#    #+#             */
/*   Updated: 2024/05/31 11:21:38 by vk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int main(int ac, char **av)
// {
//     int fd;
//     t_world data;

//     if (ac != 2 || !scene_name_check(av[1]))
//     {
//         printf("Bad arguments : Usage : ./minirt scene.rt");
//         return (EXIT_FAILURE);
//     }
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
// 		return (write(2, "File not found\n", 16), EXIT_FAILURE);
//     data = init_all_data(fd);
//     (void) data;
//     return (EXIT_SUCCESS);
// }

typedef struct s_env
{
	t_tuple	gravity;
	t_tuple	wind;
}			t_env;

typedef struct s_projectile
{
	t_tuple	position;
	t_tuple	velocity;
}			t_projectile;

void	put_pixel(t_win *win, int x, int y, unsigned int color)
{
	char	*dst;

	if ((x > SIZE_X || x < 0) || (y > SIZE_Y || y < 0))
		return ;
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	tick(t_win *win)
{
	t_projectile	pro;
	t_env			env;
	int				i;

	pro.position.x = 0;
	pro.position.y = 1;
	pro.position.z = 0;
	pro.position.w = 1;
	pro.velocity.x = 1;
	pro.velocity.y = 1.8;
	pro.velocity.z = 0;
	pro.velocity.w = 0;
	env.gravity.x = 0;
	env.gravity.y = -0.1;
	env.gravity.z = 0;
	env.gravity.w = 0;
	env.wind.x = -0.01;
	env.wind.y = 0;
	env.wind.z = 0;
	env.wind.w = 0;
	i = 0;
	pro.velocity = ft_normalization(pro.velocity);
	pro.velocity = ft_mult_vector(pro.velocity, 11.25);
	while (pro.position.y > 0)
	{
		put_pixel(win, pro.position.x, SIZE_Y - pro.position.y, 0xFFFFFF);
		pro.position = ft_sum_tuple(pro.position, pro.velocity);
		pro.velocity = ft_sum_tuple(pro.velocity, ft_sum_tuple(env.gravity,
					env.wind));
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
}

int	exit_window(t_win *win)
{
	// mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	exit(1);
	return (0);
}

t_win	*init_mlx(void)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	win->mlx = mlx_init();
	win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
	win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
	return (win);
}

// int main(int ac, char **av)
// {
//     int fd;
//     t_world data;

//     if (ac != 2 || !scene_name_check(av[1]))
//     {
//         printf("Bad arguments : Usage : ./minirt scene.rt");
//         return (EXIT_FAILURE);
//     }
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
// 		return (write(2, "File not found\n", 16), EXIT_FAILURE);
//     data = init_all_data(fd);
//     // print_all_data(&data);
//     return (EXIT_SUCCESS);
// }

unsigned int color_to_int(t_color color)
{

    if (color.r > 1)
        color.r = 1;
    if (color.g > 1)
        color.g = 1;
    if (color.b > 1)
        color.b = 1;
    int r = (unsigned int)(color.r * 255);
    int g = (unsigned int)(color.g * 255);
    int b = (unsigned int)(color.b * 255);

    return (r << 16) | (g << 8) | b;
}

int main(void) // Pour chez Urbain
{
    t_world world = ft_default_world();

    t_camera camera = ft_new_camera(11, 11, M_PI / 3);

    t_tuple from = ft_init_tuple(0, 0, -5, 1);
    t_tuple to = ft_init_tuple(0, 0, 0, 1);
    t_tuple up = ft_init_tuple(0, 1, 0, 0);

    camera.matrix = ft_view_transform(from, to, up);

    // Image ??? = render(camera, world);

    t_color color = ft_pixel_at(&world, &camera, 5, 5);

    printf("Color.r = %f\n", color.r);
    printf("Color.g = %f\n", color.g);
    printf("Color.b = %f\n", color.b);

    return (0);
}

int main(void) // Programme pour modeliser spheres avec scene
{
  t_sphere floor = ft_sphere();
  floor.transform = scaling(10, 0.01, 10);
  floor.material = ft_material();
  floor.material.color = ft_init_color(1, 0.9, 0.9);
  floor.material.specular = 0;

  t_sphere left_wall = ft_sphere();
  left_wall.transform = ft_mult_mat(translation(0, 0, 5) , rotation_y(-M_PI / 4));
  left_wall.transform = ft_mult_mat(left_wall.transform, rotation_x(M_PI / 2));
  left_wall.transform = ft_mult_mat(left_wall.transform, scaling(10, 0.01, 10));
  left_wall.material = floor.material;

  t_sphere right_wall = ft_sphere();
  right_wall.transform = ft_mult_mat(translation(0, 0, 5) , rotation_y(M_PI / 4));
  right_wall.transform = ft_mult_mat(right_wall.transform, rotation_x(M_PI / 2));
  right_wall.transform = ft_mult_mat(right_wall.transform, scaling(10, 0.01, 10));
  right_wall.material = floor.material;

  t_sphere middle = ft_sphere();
  middle.matrix = translation(-0.5, 1, 0.5);
  middle.material = ft_material();
  middle.material->color = ft_init_color(0.1, 1, 0.5);
  middle.material->diffuse = 0.7;
  middle.material->specular = 0.3;

  t_sphere right = ft_sphere();
  right.matrix = ft_mult_mat(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
  right.material = ft_material();
  right.material->color = ft_init_color(0.5, 1, 0.1);
  right.material->diffuse = 0.7;
  right.material->specular = 0.3;

  t_sphere left = ft_sphere();
  left.matrix = ft_mult_mat(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
  left.material = ft_material();
  left.material->color = ft_init_color(1, 0.8, 0.1);
  left.material->diffuse = 0.7;
  left.material->specular = 0.3;

  t_world world = ft_default_world();
  world.light = ft_point_light(ft_init_tuple(-10, 10, -10, 1), ft_init_color(1, 1, 1));

  world.camera = ft_new_camera(100, 50, M_PI / 3);
  world.camera->matrix = ft_view_transform(ft_init_tuple(0, 1.5, -5, 1), ft_init_tuple(0, 1, 0, 1), ft_init_tuple(0, 1, 0, 0));

  t_win *win = init_mlx();

  render(camera, world, win);
  mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
  mlx_loop(win->mlx);
}
