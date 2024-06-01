/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:26:12 by vk                #+#    #+#             */
/*   Updated: 2024/06/01 13:25:16 by vda-conc         ###   ########.fr       */
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
    t_tuple gravity;
    t_tuple wind;
} t_env;

typedef struct s_projectile
{
    t_tuple position;
    t_tuple velocity;
} t_projectile;

void put_pixel(t_win *win, int x, int y, unsigned int color)
{
    char *dst;

    if ((x > SIZE_X || x < 0) || (y > SIZE_Y || y < 0))
        return;
    dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void tick(t_win *win)
{
    t_projectile pro;
    t_env env;
    int i;

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

t_color ft_pixel_at(t_world *world, t_camera *camera, int x, int y)
{
    t_ray ray = ray_for_pixel(camera, x, y);
    return (ft_color_at(world, ray));
}

// int main(void) // Pour chez Urbain
// {
//     t_world *world = ft_default_world();

//     t_camera camera = ft_new_camera(11, 11, M_PI / 3);

//     t_tuple *from = ft_init_tuple(0, 0, -5, 1);
//     t_tuple *to = ft_init_tuple(0, 0, 0, 1);
//     t_tuple *up = ft_init_tuple(0, 1, 0, 0);

//     camera.matrix = ft_view_transform(*from, *to, *up);
//     t_win *win = init_mlx();
//     render(&camera, world, win);

//     t_color color = ft_pixel_at(world, &camera, 5, 5);

//     printf("Color.r = %f\n", color.r);
//     printf("Color.g = %f\n", color.g);
//     printf("Color.b = %f\n", color.b);

//     return (0);
// }

int main(void) // Tests for shadows
{

  // First test //

  t_tuple *eyev = ft_init_tuple(0, 0, -1, 0);
  t_tuple *normalv = ft_init_tuple(0, 0, -1, 0);

  t_light *light = ft_point_light(ft_init_tuple(0, 0, -10, 1), ft_color(1, 1, 1));

  t_color result = ft_lighting(ft_material(), *light, *(ft_init_tuple(0, 0, 0, 1)), *eyev, *normalv, 1);


  printf(" First test results : \n\n");


  printf("Result.r = %f | Expected : 0.1\n", result.r);
  printf("Result.g = %f | Expected : 0.1\n", result.g);
  printf("Result.b = %f | Expected : 0.1\n\n", result.b);


  // Second test //

  t_world *world = ft_default_world();
  t_tuple *point1 = ft_init_tuple(0, 10, 0, 1);

  int result2 = ft_is_shadowed(world, *point1);

  printf(" Second test results : \n\n");

  printf("Result = %d | Expected : 0\n\n", result2);

  // Third test //

  t_tuple *point2 = ft_init_tuple(10, -10, 10, 1);
  int result3 = ft_is_shadowed(world, *point2);

  printf(" Third test results : \n\n");

  printf("Result = %d | Expected : 1\n\n", result3);

  // Fourth test //

  t_tuple *point3 = ft_init_tuple(-20, 20, -20, 1);
  int result4 = ft_is_shadowed(world, *point3);

  printf(" Fourth test results : \n\n");

  printf("Result = %d | Expected : 0\n\n", result4);

  // Five test //

  t_tuple *point4 = ft_init_tuple(-2, 2, -2, 1);
  int result5 = ft_is_shadowed(world, *point4);

  printf(" Five test results : \n\n");

  printf("Result = %d | Expected : 0\n\n", result5);

  return (0);
}
