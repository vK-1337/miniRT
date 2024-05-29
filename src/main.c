/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/29 14:31:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int main(int ac, char **av)
// {
//     int fd;
//     t_data data;

//     if (ac != 2 || !scene_name_check(av[1]))
//     {
//         printf("Bad arguments : Usage : ./minirt scene.rt");
//         return EXIT_FAILURE;
//     }
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
// 		return (write(2, "File not found\n", 16), EXIT_FAILURE);
//     data = init_all_data(fd);
//     (void) data;
//     return EXIT_SUCCESS;
// }

typedef struct s_env{
    t_tuple gravity;
    t_tuple wind;
}               t_env;

typedef struct s_projectile{
    t_tuple position;
    t_tuple velocity;
}               t_projectile;

void	put_pixel(t_win *win, int x, int y, int color)
{
	char	*dst;

  if ((x > SIZE_X || x < 0)|| (y > SIZE_Y || y < 0))
    return ;
	dst = win->addr + (y * win->line_length + x
			* (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void tick(t_win *win)
{
    t_projectile pro;
    t_env env;

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

    int i;

    i = 0;
    pro.velocity = ft_normalization(pro.velocity);
    pro.velocity = ft_mult_vector(pro.velocity, 11.25);
    while (pro.position.y > 0)
    {
        put_pixel(win, pro.position.x, SIZE_Y - pro.position.y, 0xFFFFFF);
        pro.position = ft_sum_tuple(pro.position, pro.velocity);
        pro.velocity = ft_sum_tuple(pro.velocity, ft_sum_tuple(env.gravity, env.wind));
        i++;
    }
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0 );
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
//     t_data data;

//     if (ac != 2 || !scene_name_check(av[1]))
//     {
//         printf("Bad arguments : Usage : ./minirt scene.rt");
//         return EXIT_FAILURE;
//     }
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
// 		return (write(2, "File not found\n", 16), EXIT_FAILURE);
//     data = init_all_data(fd);
//     // print_all_data(&data);
//     return EXIT_SUCCESS;
// }

// int main(void)
// {
//     t_tuple direction;
//     t_tuple origin;
//     t_ray r;

//     direction.x = 1;
//     direction.y = 0;
//     direction.z = 0;
//     direction.w = 0;

//     origin.x = 2;
//     origin.y = 3;
//     origin.z = 4;
//     origin.w = 1;

//     r = ft_ray(origin, direction);

//     t_tuple position;

//     position = ft_position(r, 0);

//     printf("position.x = %f\n", position.x);
//     printf("position.y = %f\n", position.y);
//     printf("position.z = %f\n\n", position.z);

//     position = ft_position(r, 1);

//     printf("position.x = %f\n", position.x);
//     printf("position.y = %f\n", position.y);
//     printf("position.z = %f\n\n", position.z);

//     position = ft_position(r, -1);

//     printf("position.x = %f\n", position.x);
//     printf("position.y = %f\n", position.y);
//     printf("position.z = %f\n\n", position.z);

//     position = ft_position(r, 2.5);

//     printf("position.x = %f\n", position.x);
//     printf("position.y = %f\n", position.y);
//     printf("position.z = %f\n\n", position.z);

//     return (0);
// }

// int main(void)
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     t_win win;
//     int canvas_pixels = SIZE_X; // Assuming SIZE_X is the size of your canvas
//     double half = canvas_pixels / 2.0;
//     double pixel_size = 1.0; // Adjust as needed
//     double wall_z = 10.0; // Adjust as needed
//     t_tuple ray_origin = {SIZE_X / 2, SIZE_Y / 2, -5, 1}; // Adjust as needed
//     t_tuple center;

//     center.x = SIZE_X / 2;
//     center.y = SIZE_Y / 2;
//     center.z = 0;
//     center.w = 1;
//     t_sphere shape = ft_sphere(center, 1); // Initialize as needed

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, SIZE_X, SIZE_Y, "Ray Tracer");
//     win.mlx = mlx_ptr;
//     win.win = win_ptr;

//     for (int y = 0; y < canvas_pixels; y++)
//     {
//         double world_y = half - pixel_size * y;
//         for (int x = 0; x < canvas_pixels; x++)
//         {
//             double world_x = -half + pixel_size * x;
//             t_tuple position = {world_x, world_y, wall_z, 1};
//             t_tuple direction = ft_normalization(ft_dif_tuple(position, ray_origin));
//             t_ray r = ft_ray(ray_origin, direction);
//             t_intersection *xs = ft_intersect(r, shape);
//             if (ft_hit(xs, 2) != NULL)
//             {
//                 put_pixel(&win, x, y, 0xFF0000); // Red color
//             }
//         }
//     }
//     mlx_loop(mlx_ptr);
//     return (0);
// }

// int main(void)
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     t_win win;
//     t_tuple ray_origin = {CENTER_X, CENTER_Y, -5, 1}; // Adjust as needed

//     float wall_z = 10.0;
//     float wall_size = 7.0;

//     float canvas_pixels = SIZE_X;
//     float pixel_size = wall_size / canvas_pixels;

//     float half = wall_size / 2;

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, SIZE_X, SIZE_Y, "Ray Tracer");
//     win.mlx = mlx_ptr;
//     win.win = win_ptr;

//     t_tuple center = {CENTER_X, CENTER_Y, 0, 1};

//     t_sphere shape = ft_sphere(center, 1.0);

//     for ( int y = 0; y < canvas_pixels - 1; y++)
//     {
//         float world_y = half - pixel_size * y;
//         for (int x = 0; x < canvas_pixels - 1; x++)
//         {
//             float world_x = -half + pixel_size * x;
//             t_tuple position = {world_x, world_y, wall_z, 1};
//             t_tuple direction = ft_normalization(ft_dif_tuple(position, ray_origin));
//             t_ray r = ft_ray(ray_origin, direction);
//             t_intersection *xs = ft_intersect(r, shape);
//             if (ft_hit(xs, 2) != NULL)
//             {
//                 put_pixel(&win, x, y, 0xFF0000); // Red color
//             }
//         }
//     }
//     mlx_loop(mlx_ptr);
//     return (0);
// }