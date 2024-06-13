/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:26:12 by vk                #+#    #+#             */
/*   Updated: 2024/06/13 21:12:04 by udumas           ###   ########.fr       */
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


int main(int ac, char **av)
{
    int fd;
    t_world data;

    if (ac != 2 || !scene_name_check(av[1]))
    {
        printf("Bad arguments : Usage : ./minirt scene.rt");
        return (EXIT_FAILURE);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
    data = init_all_data(fd);
    printf("Camera hsize = %f\n", data.camera->hsize);
    t_win *win = init_mlx();
    render(data.camera, &data, win);
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    mlx_loop(win->mlx);
    return (EXIT_SUCCESS);
}

// t_color ft_pixel_at(t_world *world, t_camera *camera, int x, int y)
// {
//     t_ray ray = ray_for_pixel(camera, x, y);
//     return (ft_color_at(world, ray));
// }

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

// int main(void)
// {
//     // Given
//     t_world *w = ft_default_world();
//     w->light = ft_point_light(ft_init_tuple(0, 0, -10, 1), ft_color(1, 1, 1));
//     t_sphere *s1 = ft_sphere();
//     w->sphere = &s1;
//     t_sphere *s2 = ft_sphere();
//     s2->matrix = translation(0, 0, 10);
//     s1->next = s2;
//     t_ray r = ft_ray(*(ft_init_tuple(0, 0, 5, 1)), *(ft_init_tuple(0, 0, 1, 0)));
//     t_intersection i = ft_intersection(4, s2);

//     // When
//     t_comps comps = ft_prepare_computations(&i, r);
//     t_color c = ft_shade_hit(w, &comps);

//     // Then
//     printf("Color.r = %f\n", c.r);
//     printf("Color.g = %f\n", c.g);
//     printf("Color.b = %f\n", c.b);
//     return 0;
// }int main(void) // Programme pour modeliser spheres avec scene
// {
//     // t_sphere *floor = ft_sphere();
//     // floor->matrix = scaling(10, 0.01, 10);
//     // floor->material = ft_material();
//     // floor->material->color = ft_color(1, 0.9, 0.9);
//     // floor->material->specular = 0;

//     // t_sphere *left_wall = ft_sphere();
//     // left_wall->matrix = ft_mult_mat(translation(0, 0, 5), rotation_y(-M_PI / 4));
//     // left_wall->matrix = ft_mult_mat(left_wall->matrix, rotation_x(M_PI / 2));
//     // left_wall->matrix = ft_mult_mat(left_wall->matrix, scaling(10, 0.01, 10));
//     // left_wall->material = floor->material;

//     // t_sphere *right_wall = ft_sphere();
//     // right_wall->matrix = ft_mult_mat(translation(0, 0, 5), rotation_y(M_PI / 4));
//     // right_wall->matrix = ft_mult_mat(right_wall->matrix, rotation_x(M_PI / 2));
//     // right_wall->matrix = ft_mult_mat(right_wall->matrix, scaling(10, 0.01, 10));
//     // right_wall->material = floor->material;

//     t_sphere *middle = ft_sphere();
//     middle->matrix = translation(-0.5, 1, 0.5);
//     middle->material = ft_material();
//     middle->material->color = ft_color(0.1, 1, 0.5);
//     middle->material->diffuse = 0.7;
//     middle->material->specular = 0.3;

//     t_sphere *right = ft_sphere();
//     right->matrix = ft_mult_mat(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
//     right->material = ft_material();
//     right->material->color = ft_color(0.5, 1, 0.1);
//     right->material->diffuse = 0.7;
//     right->material->specular = 0.3;

//     t_sphere *left = ft_sphere();
//     left->matrix = ft_mult_mat(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
//     left->material = ft_material();
//     left->material->color = ft_color(1, 0.8, 0.1);
//     left->material->diffuse = 0.7;
//     left->material->specular = 0.3;

//     t_world *world;
//     world = malloc(sizeof(t_world));
//     world->light = ft_point_light(ft_init_tuple(0, 5, -10, 1), ft_color(1, 1, 1));
//     world->sphere = &middle;
//     middle->next = right;
//     right->next = left;
//     left->next = NULL;
//     world->sphere = NULL;
//     t_plan *plan = ft_plan();

//     t_plan *wall = ft_plan();
//     wall->matrix = ft_mult_mat(rotation_x(M_PI / 2), translation(0, 8, 0));
//     t_plan *left_wall = ft_plan();
//     left_wall->matrix = rotation_x(M_PI / 2);
//     left_wall->matrix = ft_mult_mat(rotation_y(-M_PI / 2), left_wall->matrix);
//     left_wall->matrix = ft_mult_mat(translation(5, 0, 8), left_wall->matrix);

//     t_plan *right_wall = ft_plan();
//     right_wall->matrix = ft_mult_mat(rotation_y(M_PI / 2), translation(0, 0, 0));
//     // right_wall->coord = *ft_init_tuple(-5, 0, 0, 1);
//     // right_wall->normal = ft_sum_tuple(right_wall->normal, *ft_init_tuple(1, 0, 0, 0));

//     t_plan *ceiling = ft_plan();
//     ceiling->matrix = translation(0, 10, 0);
//     ceiling->material->color = ft_color(1, 0, 0);  

//     t_cylinder *cylinder = ft_cylinder();
//     cylinder->matrix = translation(0, 0, -5);

//     t_cone *cone = ft_cone();
//     cone->matrix = translation(-3, 3, 0);
    
//     cylinder->material->color = ft_color(1, 0, 0);  
//     world->cylinder = &cylinder;
//     cylinder->next = NULL;
//     world->cone = &cone;
//     cone->next = NULL;
//     world->plan = &plan;
//     plan->next = wall;
//     wall->next = ceiling;
//     ceiling->next = left_wall;
//     left_wall->next = right_wall;
//     right_wall->next = NULL;
//     t_camera camera = ft_new_camera(SIZE_X, SIZE_Y, M_PI / 2);
//     world->camera = &camera;
//     world->camera->matrix = ft_view_transform(*ft_init_tuple(0, 7, -8, 1), *ft_init_tuple(0, 0, 0, 1), *ft_init_tuple(0, 1, 0, 0));

//     t_win *win = init_mlx();

//     render(world->camera, world, win);
//     mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
//     mlx_loop(win->mlx);
// }

// int main(void) // Programme pour modeliser spheres avec scene
// {
//     // t_sphere *floor = ft_sphere();
//     // floor->matrix = scaling(10, 0.01, 10);
//     // floor->material = ft_material();
//     // floor->material->color = ft_color(1, 0.9, 0.9);
//     // floor->material->specular = 0;

//     // t_sphere *left_wall = ft_sphere();
//     // left_wall->matrix = ft_mult_mat(translation(0, 0, 5), rotation_y(-M_PI / 4));
//     // left_wall->matrix = ft_mult_mat(left_wall->matrix, rotation_x(M_PI / 2));
//     // left_wall->matrix = ft_mult_mat(left_wall->matrix, scaling(10, 0.01, 10));
//     // left_wall->material = floor->material;

//     // t_sphere *right_wall = ft_sphere();
//     // right_wall->matrix = ft_mult_mat(translation(0, 0, 5), rotation_y(M_PI / 4));
//     // right_wall->matrix = ft_mult_mat(right_wall->matrix, rotation_x(M_PI / 2));
//     // right_wall->matrix = ft_mult_mat(right_wall->matrix, scaling(10, 0.01, 10));
//     // right_wall->material = floor->material;

//     t_sphere *middle = ft_sphere();
//     middle->matrix = translation(-0.5, 1, 0.5);
//     middle->material = ft_material();
//     middle->material->color = ft_color(0.1, 1, 0.5);
//     middle->material->diffuse = 0.7;
//     middle->material->specular = 0.3;

//     t_sphere *right = ft_sphere();
//     right->matrix = ft_mult_mat(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
//     right->material = ft_material();
//     right->material->color = ft_color(0.5, 1, 0.1);
//     right->material->diffuse = 0.7;
//     right->material->specular = 0.3;

//     t_sphere *left = ft_sphere();
//     left->matrix = ft_mult_mat(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
//     left->material = ft_material();
//     left->material->color = ft_color(1, 0.8, 0.1);
//     left->material->diffuse = 0.7;
//     left->material->specular = 0.3;

//     t_world *world;
//     world = malloc(sizeof(t_world));
    // world->light = ft_point_light(ft_init_tuple(0, 5, -10, 1), ft_color(1, 1, 1));
//     world->light->next = ft_point_light(ft_init_tuple(-5, 5, 0, 1), ft_color(1, 1, 1));
//     world->light->next->next = NULL;

//     world->sphere = &middle;
//     middle->next = right;
//     right->next = left;
//     left->next = NULL;
//     world->sphere = NULL;
//     t_plan *plan = ft_plan();

//     t_plan *wall = ft_plan();
//     wall->matrix = ft_mult_mat(rotation_x(M_PI / 2), translation(0, 8, 0));
//     t_plan *left_wall = ft_plan();
//     left_wall->matrix = rotation_x(M_PI / 2);
//     left_wall->matrix = ft_mult_mat(rotation_y(-M_PI / 2), left_wall->matrix);
//     left_wall->matrix = ft_mult_mat(translation(5, 0, 8), left_wall->matrix);

//     t_plan *right_wall = ft_plan();
//     right_wall->matrix = ft_mult_mat(rotation_y(M_PI / 2), translation(0, 0, 0));
//     // right_wall->coord = *ft_init_tuple(-5, 0, 0, 1);
//     // right_wall->normal = ft_sum_tuple(right_wall->normal, *ft_init_tuple(1, 0, 0, 0));

//     t_plan *ceiling = ft_plan();
//     ceiling->matrix = translation(0, 10, 0);
//     ceiling->material->color = ft_color(1, 0, 0);  

//     t_cylinder *cylinder = ft_cylinder();
//     cylinder->matrix = translation(0, 0, -5);

//     t_cone *cone = ft_cone();
//     cone->matrix = translation(-3, 3, 0);
    
//     cylinder->material->color = ft_color(1, 0, 0);  
//     world->cylinder = &cylinder;
//     cylinder->next = NULL;
//     world->cone = &cone;
//     cone->next = NULL;
//     world->plan = &plan;
//     plan->next = wall;
//     wall->next = ceiling;
//     ceiling->next = left_wall;
//     left_wall->next = right_wall;
//     right_wall->next = NULL;
//     t_camera camera = ft_new_camera(SIZE_X, SIZE_Y, M_PI / 2);
//     world->camera = &camera;
//    world->camera->matrix = ft_view_transform(*ft_init_tuple(0, 7, -50, 1), *ft_init_tuple(0, 0, 0, 1), *ft_init_tuple(0, 1, 0, 0));

//     t_win *win = init_mlx();

//     render(world->camera, world, win);
//     mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
//     mlx_loop(win->mlx);
// }
// void test_cone_normal()
// {
//     t_cone *cone = ft_cone();

//     struct {
//         t_tuple point;
//         t_tuple expected_normal;
//     } test_cases[] = {
//         { *ft_init_tuple(0, 0, 0, 1), *ft_init_tuple(0, 0, 0, 0) },
//         { *ft_init_tuple(1, 1, 1, 1), *ft_init_tuple(1, -sqrt(2), 1, 0) },
//         { *ft_init_tuple(-1, -1, 0, 1), *ft_init_tuple(-1, 1, 0, 0) },
//     };

//     for (int i = 0; i < 3; i++) {
//         t_tuple point = test_cases[i].point;
//         t_tuple expected_normal = test_cases[i].expected_normal;

//         t_comps object;
//         object.cone = cone;
//         object.type = CONE;

//         t_tuple calculated_normal = ft_normal_at(object, point);

//         printf("Test case %d: ", i);
//         if (ft_equal_tuple(&calculated_normal, &expected_normal)) {
//             printf("PASS\n");
//         } else {
//             printf("FAIL\n");
//             printf("Expected normal: (%f, %f, %f)\n", expected_normal.x, expected_normal.y, expected_normal.z);
//             printf("Calculated normal: (%f, %f, %f)\n", calculated_normal.x, calculated_normal.y, calculated_normal.z);
//         }
//     }
// }
// int main()
// {
//     test_cone_normal();
//     return 0;
// }
// int main(void)
// {
//     t_tuple *eyev = ft_init_tuple(0, 0, -1, 0);
//     t_tuple *normalv = ft_init_tuple(0, 0, -1, 0);
//     t_light *light = ft_point_light(ft_init_tuple(0, 0, -10, 1), ft_color(1, 1, 1));
//     int in_shadow = 1;

//     t_color c = ft_lighting(ft_material(), *light, *ft_init_tuple(0, 0, 0, 1), *eyev, *normalv, in_shadow);

//     printf("Color.r = %f\n", c.r);
//     printf("Color.g = %f\n", c.g);
//     printf("Color.b = %f\n", c.b);

//     t_world *world = ft_default_world();
//     t_tuple *point = ft_init_tuple(0, 10, 0, 1);

//     int shadowed = ft_is_shadowed(world, *point);

//     printf("Shadowed in firs test = %s\n", shadowed ? "True" : "False");

//     point = ft_init_tuple(10, -10, 10, 1);
//     shadowed = ft_is_shadowed(world, *point);

//     printf("Shadowed in second test = %s\n", shadowed ? "True" : "False");

//     point = ft_init_tuple(-20, 20, -20, 1);
//     shadowed = ft_is_shadowed(world, *point);

//     printf("Shadowed in third test = %s\n", shadowed ? "True" : "False");

//     point = ft_init_tuple(-2, 2, -2, 1);

//     shadowed = ft_is_shadowed(world, *point);

//     printf("Shadowed in fourth test = %s\n", shadowed ? "True" : "False");
// }

// int main(void)
// {
//     t_world *world = ft_default_world();

//     world->light = ft_point_light(ft_init_tuple(0, 0, -10, 1), ft_color(1, 1, 1));

//     t_sphere *s1 = ft_sphere();

//     world->sphere = &s1;

//     t_sphere *s2 = ft_sphere();

//     s2->matrix = translation(0, 0, 10);

//     s1->next = s2;

//     t_ray r = ft_ray(*ft_init_tuple(0, 0, 5, 1), *ft_init_tuple(0, 0, 1, 0));

//     t_intersection i = ft_intersection(4, s2);

//     t_comps comps = ft_prepare_computations(&i, r);

//     t_color c = ft_shade_hit(world, &comps);

//     printf("Color.r = %f\n", c.r);
//     printf("Color.g = %f\n", c.g);
//     printf("Color.b = %f\n", c.b);

//     return 0;
// }