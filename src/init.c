/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:31:50 by vda-conc         ###   ########.fr       */
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
			return (get_next_line(fd, 1), free(file_data), NULL);
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
