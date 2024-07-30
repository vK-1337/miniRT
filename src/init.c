/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 17:53:18 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_world	*init_all_data(int fd, t_win *mlx)
{
	t_world	*data;
	char	*file_data;

	data = malloc(sizeof(t_world));
	if (!data)
		return (write(STDERR_FILENO, "A malloc failed.\n", 18), NULL);
	null_data(data);
	file_data = get_next_line(fd, 0);
	if (file_data == NULL)
		return (write(3, "The file is empty\n", 19), free(data), NULL);
	if (init_corresponding_data(file_data, data, mlx) == 2)
		return (get_next_line(fd, 1), free_data(&data, mlx), free(file_data),
			NULL);
	while (file_data)
	{
		free(file_data);
		file_data = get_next_line(fd, 0);
		if (file_data && file_data[0] == '\n')
			continue ;
		if (init_corresponding_data(file_data, data, mlx) == 2)
		{
			return (get_next_line(fd, 1), free(file_data), NULL);
		}
	}
	return (data);
}

int	init_corresponding_data(char *file_data, t_world *data, t_win *mlx)
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
		return (free_data(&data, mlx), 2);
	}
	if (!init_data_w_line(data, type, data_split, mlx))
	{
		write(STDERR_FILENO, "Error initiating data.\n", 24);
		return (free_char_tab(data_split), 2);
	}
	free_char_tab(data_split);
	return (EXIT_SUCCESS);
}

int	init_data_w_line(t_world *data, t_dtype type, char **data_split, t_win *mlx)
{
	if (type == A)
	{
		if (!init_alight(data, data_split))
			return (free_data(&data, mlx), 0);
	}
	else if (type == C)
	{
		if (!init_camera(data, data_split))
			return (free_data(&data, mlx), 0);
	}
	else if (type == L)
	{
		if (!init_light(data, data_split))
			return (free_data(&data, mlx), 0);
	}
	else if (type == PL || type == SP || type == CY || type == CO)
	{
		if (!init_helper(data, type, data_split, mlx))
			return (free_data(&data, mlx), 0);
	}
	return (1);
}

int	init_helper(t_world *data, t_dtype type, char **data_split, t_win *mlx)
{
	if (type == PL)
	{
		if (!init_plan(data, data_split, mlx))
			return (0);
	}
	else if (type == SP)
	{
		if (!init_sphere(data, data_split, mlx))
			return (0);
	}
	else if (type == CY)
	{
		if (!init_cylinder(data, data_split, mlx))
			return (0);
	}
	else if (type == CO)
	{
		if (!init_cone(data, data_split, mlx))
			return (0);
	}
	return (1);
}

int	init_alight(t_world *data, char **data_split)
{
	char	**color_split;
	float	intensity;

	data->alight_intensity = ft_atof(data_split[1]);
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
	from = ft_init_tuple_reg(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(camera), 0);
	to = ft_init_tuple_reg(0, 0, 0, 1);
	up = ft_init_tuple_reg(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 0);
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
	light->intensity = (t_color){0, 0, 0, 0};
	light->colors = (t_color){0, 0, 0, 0};
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(light), 0);
	light->position.x = ft_atof(split[0]);
	light->position.y = ft_atof(split[1]);
	light->position.z = ft_atof(split[2]);
	light->position.w = 1;
	free_char_tab(split);
	intensity = ft_atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(light), 0);
	light->intensity.r = ft_atoi(split[0]) / 255.0f * intensity;
	light->intensity.g = ft_atoi(split[1]) / 255.0f * intensity;
	light->intensity.b = ft_atoi(split[2]) / 255.0f * intensity;
	light->colors = ft_color_reg(light->intensity.r, light->intensity.g,
			light->intensity.b);
	free_char_tab(split);
	light->next = NULL;
	if (!data->light)
	{
		data->light = malloc(sizeof(t_light *));
		if (!data->light)
			return (free(light), 0);
		*data->light = light;
	}
	else
		light_lstadd_back(data->light, light);
	return (1);
}

int	init_sphere(t_world *data, char **data_split, t_win *mlx)
{
	char		**split;
	t_sphere	*sphere;
	char		**color_split;
	t_color		*p_color_1;
	t_color		*p_color_2;
	char		**first_color;
	char		**second_color;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(sphere), 0);
	sphere->radius = ft_atof(data_split[2]) / 2;
	sphere->matrix = translation(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	if (!sphere->matrix)
		return (free(sphere), 0);
	sphere->center = ft_init_tuple_reg(0, 0, 0, 1);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (ft_free_mat(sphere->matrix, 4), free(sphere), 0);
	sphere->m = ft_material();
	if (!sphere->m)
		return (free_char_tab(split), ft_free_mat(sphere->matrix, 4),
			free(sphere), 0);
	sphere->m->color.r = ft_atoi(split[0]) / 255.0f;
	sphere->m->color.g = ft_atoi(split[1]) / 255.0f;
	sphere->m->color.b = ft_atoi(split[2]) / 255.0f;
	free_char_tab(split);
	if (data_split[4])
	{
		split = ft_split(data_split[4], ':');
		if (!split)
			return (free(sphere), 0);
		if (ft_strncmp(split[0], "texture", 8) == 0)
		{
			free(sphere->m);
			sphere->m = ft_texture(split[1], mlx);
			if (!sphere->m->texture)
				return (free_material(sphere->m, mlx),
					ft_free_mat(sphere->matrix, 4), free(sphere),
					free_char_tab(split), 0);
		}
		else if (ft_strncmp(split[0], "pattern", 8) == 0)
		{
			color_split = ft_split(split[1], ';');
			if (!color_split)
				return (ft_free_mat(sphere->matrix, 4), free(sphere), 0);
			first_color = ft_split(color_split[0], ',');
			if (!first_color)
				return (ft_free_mat(sphere->matrix, 4), free(sphere),
					free_char_tab(color_split), 0);
			p_color_1 = ft_color(ft_atoi(first_color[0]),
					ft_atoi(first_color[1]), ft_atoi(first_color[2]));
			if (!p_color_1)
				return (ft_free_mat(sphere->matrix, 4), free(sphere),
					free_char_tab(color_split), free_char_tab(first_color), 0);
			second_color = ft_split(color_split[1], ',');
			free_char_tab(color_split);
			p_color_2 = ft_color(ft_atoi(second_color[0]),
					ft_atoi(second_color[1]), ft_atoi(second_color[2]));
			if (!p_color_2)
				return (ft_free_mat(sphere->matrix, 4), free(sphere),
					free(p_color_1), free_char_tab(color_split), 0);
			sphere->m->pattern = ft_pattern(p_color_1, p_color_2);
			sphere->m->is_pattern = 1;
			if (!sphere->m->pattern)
				return (ft_free_mat(sphere->matrix, 4), free(sphere),
					free_char_tab(color_split), free(p_color_1),
					free(p_color_2), 0);
			free_char_tab(first_color);
			free_char_tab(second_color);
		}
		free_char_tab(split);
	}
	if (data->alight != NULL)
	{
		sphere->m->ambiant_color = data->alight;
		sphere->m->ambiant = data->alight_intensity;
	}
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

int	init_plan(t_world *data, char **data_split, t_win *mlx)
{
	char	**split;
	float	**matrix;
	char	**color_split;
	t_plan	*plan;
	t_color	*p_color_1;
	t_color	*p_color_2;
	char	**first_color;
	char	**second_color;

	plan = malloc(sizeof(t_plan));
	if (!plan)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(plan), 0);
	plan->coord.x = ft_atof(split[0]);
	plan->coord.y = ft_atof(split[1]);
	plan->coord.z = ft_atof(split[2]);
	plan->normal = ft_init_tuple_reg(0, 1, 0, 0);
	matrix = translation(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	plan->matrix = identity_matrix(4);
	plan->matrix = ft_mult_mat(plan->matrix, matrix, ALL);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(plan), 0);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_x(ft_atof(split[0])
				* M_PI), ALL);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_y(ft_atof(split[1])
				* M_PI), ALL);
	plan->matrix = ft_mult_mat(plan->matrix, rotation_z(ft_atof(split[2])
				* M_PI), ALL);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(plan), 0);
	plan->m = ft_material();
	plan->m->color.r = ft_atoi(split[0]) / 255.0f;
	plan->m->color.g = ft_atoi(split[1]) / 255.0f;
	plan->m->color.b = ft_atoi(split[2]) / 255.0f;
	plan->next = NULL;
	free_char_tab(split);
	if (data_split[4])
	{
		split = ft_split(data_split[4], ':');
		if (!split)
			return (free(plan), 0);
		if (ft_strncmp(split[0], "texture", 8) == 0)
		{
			free(plan->m);
			plan->m = ft_texture(split[1], mlx);
			if (!plan->m->texture)
				return (free(plan), free_char_tab(split), 0);
		}
		else if (ft_strncmp(split[0], "pattern", 8) == 0)
		{
			color_split = ft_split(split[1], ';');
			if (!color_split)
				return (free(plan), 0);
			first_color = ft_split(color_split[0], ',');
			if (!first_color)
				return (free(plan), free_char_tab(color_split), 0);
			p_color_1 = ft_color(ft_atoi(first_color[0]),
					ft_atoi(first_color[1]), ft_atoi(first_color[2]));
			if (!p_color_1)
				return (free(plan), free_char_tab(color_split),
					free_char_tab(first_color), 0);
			second_color = ft_split(color_split[1], ',');
			free_char_tab(color_split);
			p_color_2 = ft_color(ft_atoi(second_color[0]),
					ft_atoi(second_color[1]), ft_atoi(second_color[2]));
			if (!p_color_2)
				return (free(plan), free(p_color_1), free_char_tab(color_split),
					0);
			plan->m->pattern = ft_pattern(p_color_1, p_color_2);
			plan->m->is_pattern = 1;
			if (!plan->m->pattern)
				return (free(plan), free_char_tab(color_split), free(p_color_1),
					free(p_color_2), 0);
			free_char_tab(first_color);
			free_char_tab(second_color);
		}
		free_char_tab(split);
	}
	if (data->alight != NULL)
	{
		plan->m->ambiant_color = data->alight;
		plan->m->ambiant = data->alight_intensity;
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

int	init_cylinder(t_world *data, char **data_split, t_win *mlx)
{
	char		**split;
	t_cylinder	*cylinder;
	char		**color_split;
	t_color		*p_color_1;
	t_color		*p_color_2;
	int			y;
	char		**first_color;
	char		**second_color;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->matrix = translation(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	y = ft_atof(split[1]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->matrix = ft_mult_mat(cylinder->matrix,
			rotation_x(ft_atof(split[0]) * M_PI), ALL);
	cylinder->matrix = ft_mult_mat(cylinder->matrix,
			rotation_y(ft_atof(split[1]) * M_PI), ALL);
	cylinder->matrix = ft_mult_mat(cylinder->matrix,
			rotation_z(ft_atof(split[2]) * M_PI), ALL);
	cylinder->radius = ft_atof(data_split[3]) / 2;
	cylinder->y_max = y + ft_atof(data_split[4]) / 2;
	cylinder->y_min = y - ft_atof(data_split[4]) / 2;
	free_char_tab(split);
	split = ft_split(data_split[5], ',');
	if (!split)
		return (free(cylinder), 0);
	cylinder->m = ft_material();
	cylinder->m->color.r = ft_atoi(split[0]) / 255.0f;
	cylinder->m->color.g = ft_atoi(split[1]) / 255.0f;
	cylinder->m->color.b = ft_atoi(split[2]) / 255.0f;
	cylinder->next = NULL;
	free_char_tab(split);
	if (data->alight != NULL)
	{
		cylinder->m->ambiant_color = data->alight;
		cylinder->m->ambiant = data->alight_intensity;
	}
	if (data_split[6])
	{
		split = ft_split(data_split[6], ':');
		if (!split)
			return (free(cylinder), 0);
		if (ft_strncmp(split[0], "texture", 8) == 0)
		{
			free(cylinder->m);
			cylinder->m = ft_texture(split[1], mlx);
			if (!cylinder->m->texture)
				return (free(cylinder), free_char_tab(split), 0);
		}
		else if (ft_strncmp(split[0], "pattern", 8) == 0)
		{
			color_split = ft_split(split[1], ';');
			if (!color_split)
				return (free(cylinder), 0);
			first_color = ft_split(color_split[0], ',');
			if (!first_color)
				return (free(cylinder), free_char_tab(color_split), 0);
			p_color_1 = ft_color(ft_atoi(first_color[0]),
					ft_atoi(first_color[1]), ft_atoi(first_color[2]));
			if (!p_color_1)
				return (free(cylinder), free_char_tab(color_split),
					free_char_tab(first_color), 0);
			second_color = ft_split(color_split[1], ',');
			free_char_tab(color_split);
			p_color_2 = ft_color(ft_atoi(second_color[0]),
					ft_atoi(second_color[1]), ft_atoi(second_color[2]));
			if (!p_color_2)
				return (free(cylinder), free(p_color_1),
					free_char_tab(color_split), 0);
			cylinder->m->pattern = ft_pattern(p_color_1, p_color_2);
			cylinder->m->is_pattern = 1;
			if (!cylinder->m->pattern)
				return (free(cylinder), free_char_tab(color_split),
					free(p_color_1), free(p_color_2), 0);
			free_char_tab(first_color);
			free_char_tab(second_color);
		}
		free_char_tab(split);
	}
	if (data->alight != NULL)
	{
		cylinder->m->ambiant_color = data->alight;
		cylinder->m->ambiant = data->alight_intensity;
	}
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

int	init_cone(t_world *data, char **data_split, t_win *mlx)
{
	char	**split;
	t_cone	*cone;
	int		y;
	char	**color_split;
	t_color	*p_color_1;
	t_color	*p_color_2;
	char	**first_color;
	char	**second_color;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(cone), 0);
	cone->matrix = translation(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	y = ft_atof(split[1]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(cone), 0);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_x(ft_atof(split[0])
				* M_PI), ALL);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_y(ft_atof(split[1])
				* M_PI), ALL);
	cone->matrix = ft_mult_mat(cone->matrix, rotation_z(ft_atof(split[2])
				* M_PI), ALL);
	cone->radius = ft_atof(data_split[3]) / 2;
	cone->y_max = y + ft_atof(data_split[4]) / 2;
	cone->y_min = y - ft_atof(data_split[4]) / 2;
	free_char_tab(split);
	split = ft_split(data_split[5], ',');
	if (!split)
		return (free(cone), 0);
	cone->m = ft_material();
	cone->m->color.r = ft_atoi(split[0]) / 255.0f;
	cone->m->color.g = ft_atoi(split[1]) / 255.0f;
	cone->m->color.b = ft_atoi(split[2]) / 255.0f;
	cone->next = NULL;
	if (data_split[6])
	{
		split = ft_split(data_split[6], ':');
		if (!split)
			return (free(cone), 0);
		if (ft_strncmp(split[0], "texture", 8) == 0)
		{
			cone->m = ft_texture(split[1], mlx);
			if (!cone->m->texture)
				return (free(cone), free_char_tab(split), 0);
		}
		else if (ft_strncmp(split[0], "pattern", 8) == 0)
		{
			color_split = ft_split(split[1], ';');
			if (!color_split)
				return (free(cone), 0);
			first_color = ft_split(color_split[0], ',');
			if (!first_color)
				return (free(cone), free_char_tab(color_split), 0);
			p_color_1 = ft_color(ft_atoi(first_color[0]),
					ft_atoi(first_color[1]), ft_atoi(first_color[2]));
			if (!p_color_1)
				return (free(cone), free_char_tab(color_split),
					free_char_tab(first_color), 0);
			second_color = ft_split(color_split[1], ',');
			free_char_tab(color_split);
			p_color_2 = ft_color(ft_atoi(second_color[0]),
					ft_atoi(second_color[1]), ft_atoi(second_color[2]));
			if (!p_color_2)
				return (free(cone), free(p_color_1), free_char_tab(color_split),
					0);
			cone->m->pattern = ft_pattern(p_color_1, p_color_2);
			cone->m->is_pattern = 1;
			if (!cone->m->pattern)
				return (free(cone), free_char_tab(color_split), free(p_color_1),
					free(p_color_2), 0);
			free_char_tab(first_color);
			free_char_tab(second_color);
		}
		free_char_tab(split);
	}
	free_char_tab(split);
	if (data->alight != NULL)
	{
		cone->m->ambiant_color = data->alight;
		cone->m->ambiant = data->alight_intensity;
	}
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
	data->alight_intensity = 0;
	data->camera = NULL;
	data->cone = NULL;
	data->cylinder = NULL;
	data->light = NULL;
	data->pixel_put = NULL;
	data->plan = NULL;
	data->sphere = NULL;
	i = 0;
	while (i < 5)
		data->counter[i++] = 0;
	return ;
}
