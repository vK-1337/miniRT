/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/11 17:50:39 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_world	*init_all_data(int fd)
{
	t_world	*data;
	char	*file_data;

	data = malloc(sizeof(t_world));
	if (!data)
	{
		write(STDERR_FILENO, "A malloc failed.\n", 18);
		exit(EXIT_FAILURE);
	}
	null_data(data);
	file_data = get_next_line(fd, 0);
	if (file_data == NULL)
	{
		write(STDERR_FILENO, "The file is empty\n", 19);
		exit(EXIT_FAILURE);
	}
	if (init_corresponding_data(file_data, data) == 2)
	{
		free_data(&data);
		free(file_data);
		exit(EXIT_FAILURE);
	}
	while (file_data)
	{
		free(file_data);
		file_data = get_next_line(fd, 0);
		if (file_data && file_data[0] == '\n')
			continue ;
		if (init_corresponding_data(file_data, data) == 2)
		{
			get_next_line(fd, 1);
			free_data(&data);
			free(file_data);
			exit(EXIT_FAILURE);
		}
	}
	return (data);
}

int	init_corresponding_data(char *file_data, t_world *data)
{
	char	**data_split;
	t_dtype	type;

	if (!file_data)
		return (0);
	data_split = ft_split(file_data, ' ');
	if (!data_split)
		return (2);
	type = determine_type(data_split[0]);
	if (!type || verified_content(data_split, type) == 0)
	{
		free_char_tab(data_split);
		write(STDERR_FILENO, ".rt file content is not valid.\n", 32);
		return (2);
	}
	if (!init_data_w_line(data, type, data_split))
	{
		write(STDERR_FILENO, "A malloc failed.\n", 18);
		return (free_char_tab(data_split), 2);
	}
	free_char_tab(data_split);
	return (EXIT_SUCCESS);
}

int	init_data_w_line(t_world *data, t_dtype type, char **data_split)
{
	if (type == A)
	{
		if (!init_alight(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == C)
	{
		if (!init_camera(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == L)
	{
		if (!init_light(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == PL)
	{
		if (!init_plan(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == SP)
	{
		if (!init_sphere(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == CY)
	{
		if (!init_cylinder(data, data_split))
			return (free_data(&data), 0);
	}
	else if (type == CO)
	{
		if (!init_cone(data, data_split))
			return (free_data(&data), 0);
	}
	return (1);
}

int	init_alight(t_world *data, char **data_split)
{
	char	**color_split;
	float	intensity;

	data->alight_intensity = atof(data_split[1]);
	intensity = data->alight_intensity;
	color_split = ft_split(data_split[2], ',');
	if (!color_split)
		return (0);
	data->alight = ft_color(ft_atoi(color_split[0]) / 255.0f * intensity,
			ft_atoi(color_split[1]) / 255.0f * intensity,
			ft_atoi(color_split[2]) / 255.0f * intensity);
	if (!data->alight)
		return (0);
	free_char_tab(color_split);
	return (1);
}

int	init_camera(t_world *data, char **data_split)
{
	char		**split;
	t_camera	*camera;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;

	camera = ft_new_camera(SIZE_X, SIZE_Y, atoi(data_split[3]) * (M_PI / 180));
	if (!camera)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(camera), 0);
	from = ft_init_tuple_reg(atof(split[0]), atof(split[1]), atof(split[2]), 1);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(camera), 0);
	to = ft_init_tuple_reg(0, 0, 0, 1);
	up = ft_init_tuple_reg(atof(split[0]), atof(split[1]), atof(split[2]), 0);
	camera->matrix = ft_view_transform(from, to, up);
	free_char_tab(split);
	data->camera = camera;
	return (1);
}

int	init_light(t_world *data, char **data_split)
{
	char	**split;
	t_light	*light;
	float	intensity;

	light = malloc(sizeof(t_light));
	if (!light)
		return (0);
	light->next = NULL;
	light->position = (t_tuple){0, 0, 0, 1};
	light->intensity = (t_color){0, 0, 0};
	light->colors = (t_color){0, 0, 0};
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(light), 0);
	light->position.x = atof(split[0]);
	light->position.y = atof(split[1]);
	light->position.z = atof(split[2]);
	light->position.w = 1;
	free_char_tab(split);
	intensity = atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(light), 0);
	light->intensity.r = ft_atoi(split[0]) / 255.0f * intensity;
	light->intensity.g = ft_atoi(split[1]) / 255.0f * intensity;
	light->intensity.b = ft_atoi(split[2]) / 255.0f * intensity;
	light->colors = ft_color_reg(light->intensity.r, light->intensity.g,
			light->intensity.b);
	free_char_tab(split);
	data->light = light;
	return (1);
}

int	init_sphere(t_world *data, char **data_split)
{
	char		**split;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(sphere), 0);
	sphere->radius = atof(data_split[2]) / 2;
	sphere->matrix = translation(atof(split[0]) , atof(split[1]),
			atof(split[2]));
	sphere->center = ft_init_tuple_reg(atof(split[0]), atof(split[1]),
			atof(split[2]), 1);
	free_char_tab(split);
	
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(sphere), 0);
	sphere->material = ft_material();
	sphere->material->color.r = ft_atoi(split[0]) / 255.0f;
	sphere->material->color.g = ft_atoi(split[1]) / 255.0f;
	sphere->material->color.b = ft_atoi(split[2]) / 255.0f;
	if (data->alight != NULL)
	{
		sphere->material->ambiant_color = data->alight;
		sphere->material->ambiant = data->alight_intensity;
	}
	free_char_tab(split);
	sphere->next = NULL;
	if (!data->sphere)
	{
		data->sphere = malloc(sizeof(t_sphere *));
		if (!data->sphere)
			return (free(sphere), 0);
		*data->sphere = sphere;
	}
	else
		sphere_lstadd_back(data->sphere, sphere);
	return (1);
}

int	init_plan(t_world *data, char **data_split)
{
	char	**split;
	float	**matrix;
	t_plan	*plan;

	plan = malloc(sizeof(t_plan));
	printf("plan = %p\n", plan);
	if (!plan)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(plan), 0);
	plan->normal = ft_init_tuple_reg(0, 1, 0, 0);
	matrix = translation(atof(split[0]), atof(split[1]), atof(split[2]));
	plan->matrix = identity_matrix(4);
	plan->matrix = ft_mult_mat(plan->matrix, matrix, ALL);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(plan), 0);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_x(atof(split[0]) * M_PI),
			ALL);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_y(atof(split[1]) * M_PI),
			ALL);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_z(atof(split[2]) * M_PI),
			ALL);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(plan), 0);
	plan->material = ft_material();
	plan->material->color.r = ft_atoi(split[0]) / 255.0f;
	plan->material->color.g = ft_atoi(split[1]) / 255.0f;
	plan->material->color.b = ft_atoi(split[2]) / 255.0f;
	plan->next = NULL;
	free_char_tab(split);
	if (data->alight != NULL)
	{
		plan->material->ambiant_color = data->alight;
		plan->material->ambiant = data->alight_intensity;
	}
	if (!data->plan)
	{
		data->plan = malloc(sizeof(t_plan *));
		if (!data->plan)
			return (free(plan), 0);
		*data->plan = plan;
	}
	else
		plan_lstadd_back(data->plan, plan);
	return (1);
}

int	init_cylinder(t_world *data, char **data_split)
{
	char		**split;
	t_cylinder	*cylinder;
	int y;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->matrix = translation(atof(split[0]), atof(split[1]),
			atof(split[2]));
	y = atof(split[1]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->matrix = ft_mult_mat(cylinder->matrix, rotation_x(atoi(split[0])
				* M_PI), ALL);
	cylinder->matrix = ft_mult_mat(cylinder->matrix, rotation_y(atoi(split[1])
				* M_PI), ALL);
	cylinder->matrix = ft_mult_mat(cylinder->matrix, rotation_z(atoi(split[2])
				* M_PI), ALL);
	cylinder->radius = atof(data_split[3]) / 2;
	cylinder->y_max = y  + atof(data_split[4]) / 2;
	cylinder->y_min = y - atof(data_split[4]) / 2;
	printf("cylinder->y_max = %f\n", cylinder->y_max);
	printf("cylinder->y_min = %f\n", cylinder->y_min);
	free_char_tab(split);
	split = ft_split(data_split[5], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->material = ft_material();
	cylinder->material->color.r = ft_atoi(split[0]) / 255.0f;
	cylinder->material->color.g = ft_atoi(split[1]) / 255.0f;
	cylinder->material->color.b = ft_atoi(split[2]) / 255.0f;
	cylinder->next = NULL;
	free_char_tab(split);
	if (data->alight != NULL)
		cylinder->material->ambiant_color = data->alight;
	if (!data->cylinder)
	{
		data->cylinder = malloc(sizeof(t_cylinder *));
		if (!data->cylinder)
			return (free(cylinder), 0);
		*data->cylinder = cylinder;
	}
	else
		cylinder_lstadd_back(data->cylinder, cylinder);
	return (1);
}

int	init_cone(t_world *data, char **data_split)
{
	char	**split;
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (0);
	cone = NULL;
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(cone), 0);
	cone->matrix = translation(atof(split[0]), atof(split[1]), atof(split[2]));
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(cone), 0);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_x(atoi(split[0]) * M_PI), ALL);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_y(atoi(split[1]) * M_PI), ALL);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_z(atoi(split[2]) * M_PI), ALL);
	cone->radius = atof(data_split[3]) / 2;
	cone->y_max = atof(data_split[4]) / 2 + cone->coord.y;
	cone->y_min = -atof(data_split[4]) / 2 + cone->coord.y;
	free_char_tab(split);
	split = ft_split(data_split[5], ',');
	if (!split)
		return (free(cone), 0);
	cone->material = ft_material();
	cone->material->color.r = ft_atoi(split[0]) / 255.0f;
	cone->material->color.g = ft_atoi(split[1]) / 255.0f;
	cone->material->color.b = ft_atoi(split[2]) / 255.0f;
	cone->next = NULL;
	free_char_tab(split);
	if (data->alight != NULL)
		cone->material->ambiant_color = data->alight;
	if (!data->cone)
	{
		data->cone = malloc(sizeof(t_cone *));
		if (!data->cone)
			return (free(cone), 0);
		*data->cone = cone;
	}
	else
		cone_lstadd_back(data->cone, cone);
	return (1);
}

t_dtype	determine_type(char *data)
{
	if (strlen(data) > 2 || strlen(data) <= 0)
		return (NOTYPE);
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
		else if (data[0] == 'c' && data[1] == 'y')
			return (CY);
		else if (data[0] == 'c' && data[1] == 'o')
			return (CO);
	}
	return (NOTYPE);
}

void	null_data(t_world *data)
{
	int	i;

	data->alight = NULL;
	data->camera = NULL;
	data->cylinder = NULL;
	data->light = NULL;
	data->plan = NULL;
	data->sphere = NULL;
	data->cone = NULL;
	i = 0;
	while (i < 6)
	{
		data->counter[i] = 0;
		i++;
	}
	return ;
}
