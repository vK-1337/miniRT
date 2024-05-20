/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/20 20:06:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	init_all_data(int fd)
{
	t_data	data;
	char	*file_data;

	null_data(&data);
	file_data = get_next_line(fd);
	if (file_data == NULL)
	{
		write(STDERR_FILENO, "The file is empty\n", 19);
		exit(EXIT_FAILURE);
	}
    printf("file_data : %s", file_data);
	init_corresponding_data(file_data, &data);
	while (file_data)
	{
		free(file_data);
		file_data = get_next_line(fd);
        printf("file_data : %s", file_data);
		if (file_data && file_data[0] == '\n')
			continue ;
		if (init_corresponding_data(file_data, &data) == 2)
		{
			print_all_data(data);
			free(file_data);
			exit(EXIT_FAILURE);
		}
	}
	return (data);
}

int	init_corresponding_data(char *file_data, t_data *data)
{
	char	**data_split;
	t_dtype	type;

	if (!file_data)
		return (EXIT_FAILURE);
	data_split = ft_split(file_data, ' ');
	if (!data_split)
		return (2);
	type = determine_type(data_split[0]);
    printf("type : %d\n", type);
	if (!type)
	{
		free(data_split);
		write(STDERR_FILENO, ".rt file content is not valid.\n", 30);
		return (2);
	}
    printf("mourir\n");
	init_data_w_line(data, type, data_split);
	free(data_split);
	return (EXIT_SUCCESS);
}

void	init_data_w_line(t_data *data, t_dtype type, char **data_split)
{
	if (type == A)
		init_alight(data, data_split);
	else if (type == C)
		init_camera(data, data_split);
	else if (type == L)
		init_light(data, data_split);
	else if (type == PL)
		init_plan(data, data_split);
	else if (type == SP)
		init_sphere(data, data_split);
	else if (type == CY)
		init_cylindre(data, data_split);
}

void	init_alight(t_data *data, char **data_split)
{
	char	**color_split;
    t_alight alight;
	alight.alight = atof(data_split[1]);
	color_split = ft_split(data_split[2], ',');
	if (!color_split)
		return ;
	alight.color_r = ft_atoi(color_split[0]);
	alight.color_g = ft_atoi(color_split[1]);
	alight.color_b = ft_atoi(color_split[2]);
	free_char_tab(color_split);
    data->alight = &alight;
	return ;
}

void	init_camera(t_data *data, char **data_split)
{
	char	**split;
    t_camera camera;

	split = ft_split(data_split[1], ',');
	if (!split)
		return ;
	camera.coord_x = atof(split[0]);
	camera.coord_y = atof(split[1]);
	camera.coord_z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return ;
	camera.vector_x = atof(split[0]);
	camera.vector_y = atof(split[1]);
	camera.vector_z = atof(split[2]);
	camera.fov = atoi(data_split[3]);
	free_char_tab(split);
    data->camera = &camera;
	return ;
}

void	init_light(t_data *data, char **data_split)
{
	char	**split;
    t_light light;

	split = ft_split(data_split[1], ',');
    printf("data_split[1] : %s\n", data_split[1]);
	if (!split)
		return ;
	light.coord_x = atof(split[0]);
	light.coord_y = atof(split[1]);
	light.coord_z = atof(split[2]);
	free_char_tab(split);
	light.light_ratio = atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return ;
	light.color_r = ft_atoi(split[0]);
	light.color_g = ft_atoi(split[1]);
	light.color_b = ft_atoi(split[2]);
	free_char_tab(split);
    data->light = &light;
	return ;
}

void	init_sphere(t_data *data, char **data_split)
{
	char	**split;
    t_sphere sphere;

	split = ft_split(data_split[1], ',');
	if (!split)
		return ;
	sphere.coord_x = atof(split[0]);
	sphere.coord_y = atof(split[1]);
	sphere.coord_z = atof(split[2]);
	free_char_tab(split);
	sphere.diameter = atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return ;
	sphere.color_r = ft_atoi(split[0]);
	sphere.color_g = ft_atoi(split[1]);
	sphere.color_b = ft_atoi(split[2]);
	free_char_tab(split);
    data->sphere = &sphere;
	return ;
}

void	init_plan(t_data *data, char **data_split)
{
	char	**split;
    t_plan plan;

	split = ft_split(data_split[1], ',');
	if (!split)
		return ;
	plan.coord_x = atof(split[0]);
	plan.coord_y = atof(split[1]);
	plan.coord_z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return ;
	plan.vector_x = atof(split[0]);
	plan.vector_y = atof(split[1]);
	plan.vector_z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return ;
	plan.color_r = ft_atoi(split[0]);
	plan.color_g = ft_atoi(split[1]);
	plan.color_b = ft_atoi(split[2]);
    data->plan = &plan;
	free_char_tab(split);
}

void	init_cylindre(t_data *data, char **data_split)
{
	char	**split;
    t_cylindre cylindre;

	split = ft_split(data_split[1], ',');
	if (!split)
		return ;
	cylindre.coord_x = atof(split[0]);
	cylindre.coord_y = atof(split[1]);
	cylindre.coord_z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return ;
	cylindre.n_vector_x = atof(split[0]);
	cylindre.n_vector_y = atof(split[1]);
	cylindre.n_vector_z = atof(split[2]);
	cylindre.diameter = atof(data_split[3]);
	cylindre.height = atof(data_split[4]);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return ;
	cylindre.color_r = ft_atoi(split[0]);
	cylindre.color_g = ft_atoi(split[1]);
	cylindre.color_b = ft_atoi(split[2]);
    data->cylindre = &cylindre;
	free_char_tab(split);
}

t_dtype	determine_type(char *data)
{
	if (strlen(data) > 2 || strlen(data) <= 0)
		return (NOTYPE);
	printf("data[0] : %c\n", data[0]);
	if (strlen(data) == 1)
	{
		if (data[0] == 'A')
			return (A);
		else if (data[0] == 'C')
			return (C);
		else if (data[0] == 'L')
			return (L);
	}
	else
	{
		if (data[0] == 'p' && data[1] == 'l')
			return (PL);
		else if (data[0] == 's' && data[1] == 'p')
			return (SP);
		if (data[0] == 'c' && data[1] == 'y')
			return (CY);
	}
	return (NOTYPE);
}

void	null_data(t_data *data)
{
	data->alight = NULL;
	data->camera = NULL;
	data->cylindre = NULL;
	data->light = NULL;
	data->plan = NULL;
	data->sphere = NULL;
	return ;
}
