/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/24 17:49:23 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	print_all_data(t_data *data)
{
	printf(" Data content :\n");
	printf("\n\nData.alight : \n");
	printf("Data.aligt->alight : %f\n", data->alight->alight);
	printf("Data.aligt->color_r : %d\n", data->alight->color_r);
	printf("Data.aligt->color_g : %d\n", data->alight->color_g);
	printf("Data.aligt->color_b : %d\n", data->alight->color_b);
	printf("\n\nData.camera :\n");
	printf("Data.camera->coord_x : %f\n", data->camera->coord_x);
	printf("Data.camera->coord_y : %f\n", data->camera->coord_y);
	printf("Data.camera->coord_z : %f\n", data->camera->coord_z);
	printf("Data.camera->fov : %d\n", data->camera->fov);
	printf("Data.camera->vector_x : %f\n", data->camera->vector_x);
	printf("Data.camera->vector_y : %f\n", data->camera->vector_y);
	printf("Data.camera->vector_z : %f\n", data->camera->vector_z);
	printf("\n\nData.light :\n");
	printf("Data.light->coord_x : %f\n", data->light->coord_x);
	printf("Data.light->coord_y : %f\n", data->light->coord_y);
	printf("Data.light->coord_z : %f\n", data->light->coord_z);
	printf("Data.light->light_ratio : %f\n", data->light->light_ratio);
	printf("Data.light->color_r : %d\n", data->light->color_r);
	printf("Data.light->color_g : %d\n", data->light->color_g);
	printf("Data.light->color_b : %d\n", data->light->color_b);
    print_sphere_list(data->sphere);
    print_plan_list(data->plan);
    print_cylindre_list(data->cylindre);
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	if (ac != 2 || !scene_name_check(av[1]))
	{
		printf("Bad arguments : Usage : ./minirt scene.rt");
		return (EXIT_FAILURE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
	data = init_all_data(fd);
	print_all_data(&data);
    free_data(&data);
	return (EXIT_SUCCESS);
}

void print_sphere_list(t_sphere **sphere_list)
{
	t_sphere	*tmp;
	int			i;

	i = 1;
	tmp = *sphere_list;
	while (tmp)
	{
		printf("\n\nSphere number : %d\n", i);
		printf("Sphere coord_x : %f\n", tmp->coord_x);
		printf("Sphere coord_y : %f\n", tmp->coord_y);
		printf("Sphere coord_z : %f\n", tmp->coord_z);
		printf("Sphere diameter : %f\n", tmp->diameter);
		printf("Sphere color_r : %d\n", tmp->color_r);
		printf("Sphere color_g : %d\n", tmp->color_g);
		printf("Sphere color_b : %d\n", tmp->color_b);
		tmp = tmp->next;
		i++;
	}
}

void print_plan_list(t_plan **plan_list)
{
    t_plan	*tmp;
    int		i;

    i = 1;
    tmp = *plan_list;
    while (tmp)
    {
        printf("\n\nPlan number : %d\n", i);
        printf("Plan coord_x : %f\n", tmp->coord_x);
        printf("Plan coord_y : %f\n", tmp->coord_y);
        printf("Plan coord_z : %f\n", tmp->coord_z);
        printf("Plan vector_x : %f\n", tmp->vector_x);
        printf("Plan vector_y : %f\n", tmp->vector_y);
        printf("Plan vector_z : %f\n", tmp->vector_z);
        printf("Plan color_r : %d\n", tmp->color_r);
        printf("Plan color_g : %d\n", tmp->color_g);
        printf("Plan color_b : %d\n", tmp->color_b);
        tmp = tmp->next;
        i++;
    }
}

void print_cylindre_list(t_cylindre **cylindre_list)
{
    t_cylindre	*tmp;
    int			i;

    i = 1;
    tmp = *cylindre_list;
    while (tmp)
    {
        printf("Cylindre number : %d\n", i);
        printf("Cylindre coord_x : %f\n", tmp->coord_x);
        printf("Cylindre coord_y : %f\n", tmp->coord_y);
        printf("Cylindre coord_z : %f\n", tmp->coord_z);
        printf("Cylindre n_vector_x : %f\n", tmp->n_vector_x);
        printf("Cylindre n_vector_y : %f\n", tmp->n_vector_y);
        printf("Cylindre n_vector_z : %f\n", tmp->n_vector_z);
        printf("Cylindre diameter : %f\n", tmp->diameter);
        printf("Cylindre height : %f\n", tmp->height);
        printf("Cylindre color_r : %d\n", tmp->color_r);
        printf("Cylindre color_g : %d\n", tmp->color_g);
        printf("Cylindre color_b : %d\n", tmp->color_b);
        tmp = tmp->next;
        i++;
    }
}
