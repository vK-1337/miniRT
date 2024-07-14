/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/14 18:20:46 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void put_pixel(t_win *win, int x, int y, unsigned int color)
{
    char *dst;

    if ((x > SIZE_X || x < 0) || (y > SIZE_Y || y < 0))
    {
        printf("x: %d, y: %d\n", x, y);
        return;
    }
    dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void ft_free_all(t_complete **complete)
{
    free_data(&(*complete)->data);
}

int exit_window(t_complete *complete)
{
    t_win *win = complete->win;
    mlx_destroy_image(win->mlx, win->img);
    mlx_destroy_window(win->mlx, win->win);
    mlx_destroy_display(win->mlx);
    free(win->mlx);
    free(win);
    ft_free_all(&complete);
    free(complete);
    exit(0);
    return (0);
}

t_win *init_mlx(void)
{
    t_win *win;

    win = malloc(sizeof(t_win));
    win->mlx = mlx_init();
    if (!win->mlx)
        return (NULL);
    win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
    win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
    win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
                                  &win->line_length, &win->endian);
    return (win);
}

void start_threads(t_complete *complete)
{
    int i;
    int start_x;
    int start_y;
    int end_x;
    int end_y;

    start_x = 0;
    start_y = 0;
    end_x = SIZE_X / 10;
    end_y = SIZE_Y / 10;
    complete->thread = malloc(sizeof(t_thread) * (10 *10));
    complete->data->pixel_put = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(complete->data->pixel_put, NULL);
    i = 0;
    while (i < 10 * 10)       {
        complete->thread[i].start_x = start_x;
        complete->thread[i].start_y = start_y;
        complete->thread[i].end_x = end_x;
        complete->thread[i].end_y = end_y;
        complete->thread[i].index = i;
        complete->thread[i].win = complete->win;
        complete->thread[i].data = complete->data;
        pthread_create(&complete->thread[i].pthread_id, NULL, render, &complete->thread[i]);
        start_x = end_x;
        end_x += SIZE_X / 10;
        if (start_x == SIZE_X)
        {
            start_x = 0;
            end_x = SIZE_X / 10;
            start_y = end_y;
            end_y += SIZE_Y / 10;
        }
        if (start_y == SIZE_Y)
        {
            start_y = i  * SIZE_Y / 10;
            end_y = start_y + SIZE_Y / 10;
        }
        if (end_x > SIZE_X)
            end_x = SIZE_X;
        if (end_y > SIZE_Y)
            end_y = SIZE_Y;
        i++;
    }
    i--;
    while (i >= 0)
    {
        pthread_join(complete->thread[i].pthread_id, NULL);
        i--;
    }
    free(complete->thread);
    pthread_mutex_destroy(complete->data->pixel_put);
    free(complete->data->pixel_put);
}




int main(int ac, char **av)
{
    int fd;
    t_world *data;
    if (ac != 2 || !scene_name_check(av[1]))
    {
        printf("Bad arguments : Usage : ./minirt scene.rt");
        return (EXIT_FAILURE);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (write(2, "File not found\n", 16), EXIT_FAILURE);
    data = init_all_data(fd);
    t_win *win = init_mlx();
    if (!win)
        return (free_data(&data), EXIT_FAILURE);
    t_complete *complete = malloc(sizeof(t_complete));
    complete->data = data;
    complete->win = win;
    start_threads(complete);
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
    mlx_hook(win->win, 17, 0, exit_window, complete);
    mlx_loop(win->mlx);
    return (EXIT_SUCCESS);
}


// int main(void)
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
//     middle->material->specular = 0.4;
//     printf("middle\n");
//     print_matrix(middle->matrix, 4);
//     printf("\n");
//     // t_sphere *right = ft_sphere();
//     // right->matrix = ft_mult_mat(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
//     // right->material = ft_material();
//     // right->material->color = ft_color(0.5, 1, 0.1);
//     // right->material->diffuse = 0.7;
//     // right->material->specular = 0.3;

//     // t_sphere *left = ft_sphere();
//     // left->matrix = ft_mult_mat(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
//     // left->material = ft_material();
//     // left->material->color = ft_color(1, 0.8, 0.1);
//     // left->material->diffuse = 0.7;
//     // left->material->specular = 0.3;

//     t_world *world;
//     world = malloc(sizeof(t_world));
//     world->light = ft_point_light(ft_init_tuple(0, 5, -10, 1), ft_color(1, 1, 1));
//     world->light->next = ft_point_light(ft_init_tuple(-5, 5, 0, 1), ft_color(1, 1, 1));
//     world->light->next->next = NULL;
//     printf ("light\n");
//     printf ("light->position: %f %f %f\n", world->light->position.x, world->light->position.y, world->light->position.z);
//     printf ("light->intensity: %f %f %f\n", world->light->intensity.r, world->light->intensity.g, world->light->intensity.b);

//     world->sphere = &middle;
//     // middle->next = right;
//     // right->next = left;
//     // left->next = NULL;
//     (*world->sphere)->next = NULL;
//     t_plan *plan = ft_plan();
//     printf("plan\n");
//     print_matrix(plan->matrix, 4);
//     printf("\n");
//     t_plan *wall = ft_plan();
//     wall->matrix = ft_mult_mat(rotation_x(M_PI / 2), translation(0, 8, 0));
//     printf("wall\n");
//     print_matrix(wall->matrix, 4);
//     printf("\n");
//     t_plan *left_wall = ft_plan();
//     left_wall->matrix = rotation_x(M_PI / 2);
//     left_wall->matrix = ft_mult_mat(rotation_y(-M_PI / 2), left_wall->matrix);
//     left_wall->matrix = ft_mult_mat(translation(5, 0, 0), left_wall->matrix);

//     t_plan *right_wall = ft_plan();
//     right_wall->matrix = rotation_x(M_PI / 2);
//     right_wall->matrix = ft_mult_mat(rotation_y(M_PI / 2), right_wall->matrix);
//     right_wall->matrix = ft_mult_mat(translation(-5, 0, 0), right_wall->matrix);

//     // right_wall->coord = *ft_init_tuple(-5, 0, 0, 1);
//     // right_wall->normal = ft_sum_tuple(right_wall->normal, *ft_init_tuple(1, 0, 0, 0));

//     t_plan *ceiling = ft_plan();
//     ceiling->matrix = translation(0, 10, 0);
//     ceiling->material->color = ft_color(1, 0, 0);
//     printf("ceiling\n");
//     print_matrix(ceiling->matrix, 4);
//     printf("\n");

//     // t_cylinder *cylinder = ft_cylinder();
//     // cylinder->matrix = translation(0, 0, -5);

//     // t_cone *cone = ft_cone();
//     // cone->matrix = translation(-3, 3, 0);

//     // cylinder->material->color = ft_color(1, 0, 0);
//     // world->cylinder = &cylinder;
//     // cylinder->next = NULL;
//     // world->cone = &cone;
//     // cone->next = NULL;
//     world->plan = &plan;
//     plan->next = wall;
//     wall->next = ceiling;
//     ceiling->next = NULL;
//     // left_wall;
//     // left_wall->next = right_wall;
//     // right_wall->next = NULL;
//     t_camera camera = *ft_new_camera(SIZE_X, SIZE_Y, M_PI / 2);
//     world->camera = &camera;
//    world->camera->matrix = ft_view_transform(*ft_init_tuple(0, 7, -50, 1), *ft_init_tuple(0, 0, 0, 1), *ft_init_tuple(0, 1, 0, 0));
//     print_matrix(world->camera->matrix, 4);
//     printf("camera->matrix:\n");
// 	print_matrix(world->camera->matrix, 4);
// 	printf("\n");
// 	printf("camera->pixel_size: %f\n", world->camera->pixel_size);
// 	printf("camera->half_width: %f\n", world->camera->half_width);
// 	printf("camera->half_height: %f\n", world->camera->half_height);
// 	printf("camera->hsize: %f\n", world->camera->hsize);
// 	printf("camera->vsize: %f\n", world->camera->vsize);
// 	printf("camera->fov: %f\n", world->camera->fov);
// 	printf("vector: %f, %f, %f\n", world->camera->matrix[0][0], world->camera->matrix[0][1], world->camera->matrix[0][2]);
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
//     world->light = ft_point_light(ft_init_tuple(0, 9, -5, 1), ft_color(1, 1, 1));
//     printf("light\n");
//     printf("light->position: %f %f %f\n", world->light->position.x, world->light->position.y, world->light->position.z);
//     printf("light->intensity: %f %f %f\n", world->light->intensity.r, world->light->intensity.g, world->light->intensity.b);
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
//     printf("ceiling\n");
//     print_matrix(ceiling->matrix, 4);
//     printf("\n");

//     t_cylinder *cylinder = ft_cylinder();
//     cylinder->matrix = translation(0, 0, -5);
//     cylinder->radius = 3;

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
//     t_camera camera = *ft_new_camera(SIZE_X, SIZE_Y, M_PI / 2);
//     world->camera = &camera;
//     world->camera->matrix = ft_view_transform(*ft_init_tuple(0, 6, -10, 1), *ft_init_tuple(0, 0, 0, 1), *ft_init_tuple(0, 1, 0, 0));

//     t_win *win = init_mlx();

//     render(world->camera, world, win);
//     mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
//     mlx_loop(win->mlx);
// }
