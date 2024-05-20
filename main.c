/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/20 19:30:29 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_all_data(t_data data)
{
    printf(" Data content :\n");
    printf("\n\nData.alight : \n");
    printf("Data.aligt->alight : %f\n", data.alight->alight);
    printf("Data.aligt->color_r : %d\n", data.alight->color_r);
    printf("Data.aligt->color_g : %d\n", data.alight->color_g);
    printf("Data.aligt->color_b : %d\n", data.alight->color_b);
    printf("\n\nData.camera :\n");
    printf("Data.camera->coord_x : %f\n", data.camera->coord_x);
    printf("Data.camera->coord_y : %f\n", data.camera->coord_y);
    printf("Data.camera->coord_z : %f\n", data.camera->coord_z);
    printf("Data.camera->fov : %d\n", data.camera->fov);
    printf("Data.camera->vector_x : %f\n", data.camera->vector_x);
    printf("Data.camera->vector_y : %f\n", data.camera->vector_y);
    printf("Data.camera->vector_z : %f\n", data.camera->vector_z);
    printf("\n\nData.cylindre :\n");
    printf("Data.cylindre->coord_x : %f\n", data.cylindre->coord_x);
    printf("Data.cylindre->coord_y : %f\n", data.cylindre->coord_y);
    printf("Data.cylindre->coord_z : %f\n", data.cylindre->coord_z);
    printf("Data.cylindre->diameter : %f\n", data.cylindre->diameter);
    printf("Data.cylindre->height : %f\n", data.cylindre->height);
    printf("Data.cylindre->color_r : %d\n", data.cylindre->color_r);
    printf("Data.cylindre->color_g : %d\n", data.cylindre->color_g);
    printf("Data.cylindre->color_b : %d\n", data.cylindre->color_b);
    printf("\n\nData.plan :\n");
    printf("Data.plan->coord_x : %f\n", data.plan->coord_x);
    printf("Data.plan->coord_y : %f\n", data.plan->coord_y);
    printf("Data.plan->coord_z : %f\n", data.plan->coord_z);
    printf("Data.plan->vector_x : %f\n", data.plan->vector_x);
    printf("Data.plan->vector_y : %f\n", data.plan->vector_y);
    printf("Data.plan->vector_z : %f\n", data.plan->vector_z);
    printf("Data.plan->color_r : %d\n", data.plan->color_r);
    printf("Data.plan->color_g : %d\n", data.plan->color_g);
    printf("Data.plan->color_b : %d\n", data.plan->color_b);
    printf("\n\nData.sphere :\n");
    printf("Data.sphere->coord_x : %f\n", data.sphere->coord_x);
    printf("Data.sphere->coord_y : %f\n", data.sphere->coord_y);
    printf("Data.sphere->coord_z : %f\n", data.sphere->coord_z);
    printf("Data.sphere->diameter : %f\n", data.sphere->diameter);
    printf("Data.sphere->color_r : %d\n", data.sphere->color_r);
    printf("Data.sphere->color_g : %d\n", data.sphere->color_g);
    printf("Data.sphere->color_b : %d\n", data.sphere->color_b);
    printf("\n\nData.light :\n");
    printf("Data.light->coord_x : %f\n", data.light->coord_x);
    printf("Data.light->coord_y : %f\n", data.light->coord_y);
    printf("Data.light->coord_z : %f\n", data.light->coord_z);
    printf("Data.light->light_ratio : %f\n", data.light->light_ratio);
    printf("Data.light->color_r : %d\n", data.light->color_r);
    printf("Data.light->color_g : %d\n", data.light->color_g);
    printf("Data.light->color_b : %d\n", data.light->color_b);
}

int main(int ac, char **av)
{
    int fd;
    t_data data;

    if (ac != 2 || !scene_name_check(av[1]))
    {
        printf("Bad arguments : Usage : ./minirt scene.rt");
        return EXIT_FAILURE;
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
    data = init_all_data(fd);
    print_all_data(data);
    return EXIT_SUCCESS;
}
