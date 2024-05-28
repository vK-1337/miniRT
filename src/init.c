/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/28 10:56:55 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_data	init_all_data(int fd)
{
	t_data	data;
	char	*file_data;

	null_data(&data);
	file_data = get_next_line(fd, 0);
	if (file_data == NULL)
	{
		write(STDERR_FILENO, "The file is empty\n", 19);
		exit(EXIT_FAILURE);
	}
	if (init_corresponding_data(file_data, &data) == 2)
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
		if (init_corresponding_data(file_data, &data) == 2)
		{
            get_next_line(fd, 1);
            free_data(&data);
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

int	init_data_w_line(t_data *data, t_dtype type, char **data_split)
{
	if (type == A)
	{
		if (!init_alight(data, data_split))
			return (free_data(data), 0);
	}
	else if (type == C)
	{
		if (!init_camera(data, data_split))
			return (free_data(data), 0);
	}
	else if (type == L)
	{
		if (!init_light(data, data_split))
			return (free_data(data), 0);
	}
	else if (type == PL)
	{
		if (!init_plan(data, data_split))
			return (free_data(data), 0);
	}
	else if (type == SP)
	{
		if (!init_sphere(data, data_split))
			return (free_data(data), 0);
	}
	else if (type == CY)
	{
		if (!init_cylindre(data, data_split))
			return (free_data(data), 0);
	}
	return (1);
}

int	init_alight(t_data *data, char **data_split)
{
	char		**color_split;
	t_alight	*alight;

	alight = malloc(sizeof(t_alight));
	if (!alight)
		return (0);
	alight->alight = atof(data_split[1]);
	color_split = ft_split(data_split[2], ',');
	if (!color_split)
		return (free(alight), 0);
    alight->colors.r = ft_atoi(color_split[0]);
	alight->colors.g = ft_atoi(color_split[1]);
	alight->colors.b = ft_atoi(color_split[2]);
	free_char_tab(color_split);
	data->alight = alight;
	return (1);
}

int	init_camera(t_data *data, char **data_split)
{
	char		**split;
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(camera) , 0);
	camera->coord.x = atof(split[0]);
	camera->coord.y = atof(split[1]);
	camera->coord.z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(camera) , 0);
	camera->vector.x = atof(split[0]);
	camera->vector.y = atof(split[1]);
	camera->vector.z = atof(split[2]);
	camera->fov = atoi(data_split[3]);
	free_char_tab(split);
	data->camera = camera;
	return (1);
}

int	init_light(t_data *data, char **data_split)
{
	char	**split;
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(light) ,0);
	light->coord.x = atof(split[0]);
	light->coord.y = atof(split[1]);
	light->coord.z = atof(split[2]);
	free_char_tab(split);
	light->light_ratio = atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(light) ,0);
	light->colors.r = ft_atoi(split[0]);
	light->colors.g = ft_atoi(split[1]);
	light->colors.b = ft_atoi(split[2]);
	free_char_tab(split);
	data->light = light;
	return (1);
}

int	init_sphere(t_data *data, char **data_split)
{
    char		**split;
    t_sphere	*sphere;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (0);
    split = ft_split(data_split[1], ',');
    if (!split)
        return (free(sphere) , 0);
    sphere->center.x = atof(split[0]);
    sphere->center.y = atof(split[1]);
    sphere->center.z = atof(split[2]);
    free_char_tab(split);
    sphere->diameter = atof(data_split[2]);
    split = ft_split(data_split[3], ',');
    if (!split)
        return (free(sphere) , 0);
    sphere->colors.r = ft_atoi(split[0]);
    sphere->colors.g = ft_atoi(split[1]);
    sphere->colors.b = ft_atoi(split[2]);
    free_char_tab(split);
    sphere->matrix = identity_matrix(4);
    sphere->next = NULL;
    if (!data->sphere)
    {
        data->sphere = malloc(sizeof(t_sphere*));
        if (!data->sphere)
            return (free(sphere), 0);
        *data->sphere = sphere;
    }
    else
        sphere_lstadd_back(data->sphere, sphere);
    return (1);
}

int	init_plan(t_data *data, char **data_split)
{
	char	**split;
	t_plan	*plan;

	plan = malloc(sizeof(t_plan));
	if (!plan)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(plan), 0);
	plan->coord.x = atof(split[0]);
	plan->coord.y = atof(split[1]);
	plan->coord.z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(plan), 0);
	plan->vector.x = atof(split[0]);
	plan->vector.y = atof(split[1]);
	plan->vector.z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(plan), 0);
	plan->colors.r = ft_atoi(split[0]);
	plan->colors.g = ft_atoi(split[1]);
	plan->colors.b = ft_atoi(split[2]);
    plan->next = NULL;
    free_char_tab(split);
    if (!data->plan)
    {
        data->plan = malloc(sizeof(t_plan*));
        if (!data->plan)
            return (free(plan), 0);
        *data->plan = plan;
    }
    else
	    plan_lstadd_back(data->plan, plan);
	return (1);
}

int	init_cylindre(t_data *data, char **data_split)
{
	char		**split;
	t_cylindre	*cylindre;

	cylindre = malloc(sizeof(t_cylindre));
	if (!cylindre)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(cylindre), 0);
	cylindre->coord.x = atof(split[0]);
	cylindre->coord.y = atof(split[1]);
	cylindre->coord.z = atof(split[2]);
	free_char_tab(split);
	split = ft_split(data_split[2], ',');
	if (!split)
		return (free(cylindre), 0);
	cylindre->n_vector.x = atof(split[0]);
	cylindre->n_vector.y = atof(split[1]);
	cylindre->n_vector.z = atof(split[2]);
	cylindre->diameter = atof(data_split[3]);
	cylindre->height = atof(data_split[4]);
	free_char_tab(split);
	split = ft_split(data_split[5], ',');
	if (!split)
		return (free(cylindre), 0);
	cylindre->colors.r = ft_atoi(split[0]);
	cylindre->colors.g = ft_atoi(split[1]);
	cylindre->colors.b = ft_atoi(split[2]);
    cylindre->next = NULL;
    free_char_tab(split);
    if (!data->cylindre)
    {
        data->cylindre = malloc(sizeof(t_cylindre*));
        if (!data->cylindre)
            return (free(cylindre), 0);
        *data->cylindre = cylindre;
    }
    else
	    cylindre_lstadd_back(data->cylindre, cylindre);
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
		if (data[0] == 'c' && data[1] == 'y')
			return (CY);
	}
	return (NOTYPE);
}

void	null_data(t_data *data)
{
	int	i;

	data->alight = NULL;
	data->camera = NULL;
	data->cylindre = NULL;
	data->light = NULL;
	data->plan = NULL;
	data->sphere = NULL;
	i = 0;
	while (i < 6)
	{
		data->counter[i] = 0;
		i++;
	}
	return ;
}