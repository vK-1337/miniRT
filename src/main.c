/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/30 17:15:28 by vda-conc         ###   ########.fr       */
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
//     t_data data;

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

int main(void)
{
    t_tuple ray_origin = {0, 0, -5, 1};
    t_tuple center = {0, 0, 0, 1};
    t_sphere sphere = ft_sphere(center, 1);
    double wall_z = 10.0;
    double wall_size = 7.0;
    double canvas_pixels = SIZE_X;
    double pixel_size = wall_size / canvas_pixels;
    double half = wall_size / 2;
    t_win *win;

    t_material *m = ft_material();

    sphere.material = m;
    sphere.material->color->r = 1;
    sphere.material->color->g = 0.2;
    sphere.material->color->b = 1;

    t_tuple light_position = {-10, 10, -10, 1};
    t_color light_color = {1, 1, 1};
    t_light light = ft_point_light(&light_position, &light_color);

    win = init_mlx();
    for ( int y = 0; y < canvas_pixels - 1; y++)
    {
        double world_y = half - pixel_size * y;
        for (int x = 0; x < canvas_pixels - 1; x++)
        {
            double world_x = -half + pixel_size * x;
            t_tuple position = {world_x, world_y, wall_z, 1};
            t_tuple direction = ft_normalization(ft_dif_tuple(position,
			ray_origin));
            t_ray r = ft_ray(ray_origin, direction);
            t_intersection *xs = ft_intersect(r, &sphere);
            if (ft_hit(xs, 2) != NULL)
            {
                t_tuple point = ft_position(r, xs->t);
                t_tuple normal = ft_normal_at(*xs->object, point);
                t_tuple eye = ft_neg_tuple(r.direction);
                t_color color = ft_lighting(xs->object->material, light, point, eye, normal);
                put_pixel(win, x, y, color_to_int(color));
            }
        }
    }
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    mlx_loop(win->mlx);
    return (0);
}

// int	main(void)
// {
//     t_tuple position = {0, 0, 0, 1};
//     t_color intensity = {1, 1, 1};
// 	t_light light;normal_at

//     printf("TESTING LIGHT \n\n");
//     light = ft_point_light(&position, &intensity);

//     printf("position x = %f\n", light.position.x);
//     printf("position y = %f\n", light.position.y);
//     printf("position z = %f\n", light.position.z);
//     printf("position w = %f\n", light.position.w);

//     printf("intensity r = %u\n", light.intensity.r);
//     printf("intensity g = %u\n", light.intensity.g);
//     printf("intensity b = %u\n\n", light.intensity.b);


//     printf("TESTING MATERIAL \n\n");

//     t_material *m = ft_material();

//     printf("color r = %u\n", m->color->r);
//     printf("color g = %u\n", m->color->g);
//     printf("color b = %u\n", m->color->b);

//     printf("ambient = %f\n", m->ambient);
//     printf("diffuse = %f\n", m->diffuse);
//     printf("specular = %f\n", m->specular);
//     printf("shininess = %f\n\n", m->shininess);

//     printf("Testing sphere assignatiolight_dot_normaln\n\n");

//     t_sphere s = ft_sphere(position, 1);

//     printf("color r = %u\n", s.material->color->r);
//     printf("color g = %u\n", s.material->color->g);
//     printf("color b = %u\n", s.material->color->b);

//     printf("ambient = %f\n", s.material->ambient);
//     printf("diffuse = %f\n", s.material->diffuse);
//     printf("specular = %f\n", s.material->specular);
//     printf("shininess = %f\n\n", s.material->shininess);

//     t_material *m2 = ft_material();
//     m2->ambient = 1;

//     s.material = m2;
//     printf("Testing after assignation\n\n");

//     printf("color r = %u\n", s.material->color->r);
//     printf("color g = %u\n", s.material->color->g);
//     printf("color b = %u\n", s.material->color->b);

//     printf("ambient = %f\n", s.material->ambient);
//     printf("diffuse = %f\n", s.material->diffuse);
//     printf("specular = %f\n", s.material->specular);
//     printf("shininess = %f\n\n", s.material->shininess);
// 	return (0);
// }

int main(void)
{


    return (0);
}