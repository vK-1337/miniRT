/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:52 by vda-conc          #+#    #+#             */
/*   Updated: 2024/06/05 19:31:33 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	scene_name_check(char *av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	if (i <= 1)
		return (0);
	if (av[i - 1] != 't' && av[i - 2] != 'r' && av[i - 3] != '.')
		return (0);
	if (!av[i - 4])
		return (0);
	return (1);
}
int	verified_content(char **data, t_dtype type)
{
	if (type == A)
		return (verify_alight(data));
	else if (type == C)
		return (verify_camera(data));
	else if (type == L)
		return (verify_light(data));
	else if (type == PL)
		return (verify_plan(data));
	else if (type == SP)
		return (verify_sphere(data));
	else if (type == CY)
		return (verify_cylinder(data));
	return (0);
}

int	verify_alight(char **data)
{
	int		i;
	float	float_data;

	i = 1;
	if (char_tab_len(data) != 3)
		return (0);
	while (data[i])
	{
		if (i == 1)
		{
			if (!is_string_float(data[i]))
				return (0);
			float_data = atof(data[i]);
			if (float_data < 0.0 || float_data > 1.0)
				return (0);
		}
		else if (i == 2)
		{
			if (!verify_colors(data[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

int	verify_camera(char **data)
{
	if (char_tab_len(data) != 4)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!verify_fov(data[3]))
		return (0);
	return (1);
}

int	verify_fov(char *data)
{
	int	fov;

	if (!data || !check_fov_syntax(data))
		return (0);
	fov = ft_atoi(data);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

int	check_fov_syntax(char *data)
{
	int	i;

	if (!data || (ft_strlen(data) > 3 && data[ft_strlen(data) - 1] != '\n'))
		return (0);
	i = 0;
	while (data[i])
	{
		if (!ft_isdigit(data[i]) && (data[i] != '\n' && !data[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	verify_vect(char *data)
{
	int		i;
	char	**vect_split;
	float	vect;

	if (!check_vect_syntax(data))
		return (0);
	vect_split = ft_split(data, ',');
	if (!vect_split)
		return (0);
	if (char_tab_len(vect_split) != 3)
		return (free_char_tab(vect_split), 0);
	i = 0;
	while (vect_split[i])
	{
		vect = atof(vect_split[i]);
		if (vect > 1.0 || vect < -1.0)
			return (free_char_tab(vect_split), 0);
		i++;
	}
	free_char_tab(vect_split);
	return (1);
}

int	check_vect_syntax(char *data) // ! OK
{
	int i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '-' && (!data[i + 1] || !ft_isdigit(data[i + 1])
				|| (data[i - 1] && data[i - 1] != ',')))
			return (0);
		else if (data[i] == '.' && (!data[i - 1] || !data[i + 1]
				|| !ft_isdigit(data[i + 1]) || !ft_isdigit(data[i - 1])))
			return (0);
		else if (data[i] == ',' && (!data[i - 1] || !data[i + 1]
				|| (!ft_isdigit(data[i + 1]) && data[i + 1] != '-')
				|| !ft_isdigit(data[i - 1])))
			return (0);
		else if (!ft_isdigit(data[i]) && data[i] != '.' && data[i] != '-'
			&& data[i] != ',')
			return (0);
		else if (ft_isdigit(data[i]) && data[i] != '1' && data[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

int	verify_coord(char *data) // ! OK
{
	char **coord_split;

	if (!check_coord_syntax(data))
		return (0);
	coord_split = ft_split(data, ',');
	if (!coord_split)
		return (0);
	if (char_tab_len(coord_split) != 3)
		return (free_char_tab(coord_split), 0);
	free_char_tab(coord_split);
	return (1);
}

int	check_coord_syntax(char *data) // ! OK
{
	int i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '-' && (!data[i + 1] || !ft_isdigit(data[i + 1])
				|| (i > 0 && data[i - 1] && data[i - 1] != ',')))
			return (0);
		else if (data[i] == '.' && (!data[i - 1] || !data[i + 1]
				|| !ft_isdigit(data[i + 1]) || !ft_isdigit(data[i - 1])))
			return (0);
		else if (data[i] == ',' && (!data[i - 1] || !data[i + 1]
				|| (!ft_isdigit(data[i + 1]) && data[i + 1] != '-')
				|| !ft_isdigit(data[i - 1])))
			return (0);
		else if (!ft_isdigit(data[i]) && data[i] != '.' && data[i] != '-'
			&& data[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

int	verify_light(char **data)
{
	float	float_data;

	if (char_tab_len(data) != 4)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!is_string_float(data[2]))
		return (0);
	float_data = atof(data[2]);
	if (float_data < 0.0 || float_data > 1.0)
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	return (1);
}

int	verify_sphere(char **data)
{
	print_char_tab(data);
	if (char_tab_len(data) != 4)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!is_string_float(data[2]))
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	return (1);
}

int	verify_plan(char **data)
{
	if (char_tab_len(data) != 4)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	return (1);
}

int	verify_cylinder(char **data)
{
	if (char_tab_len(data) != 6)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!is_string_float(data[3]) || !is_string_float(data[4]))
		return (0);
	if (!verify_colors(data[5]))
		return (0);
	return (1);
}

int	verify_colors(char *data)
{
	char	**colors_split;
	int		color_int;
	int		i;

	if (!verify_colors_syntax(data))
		return (0);
	colors_split = ft_split(data, ',');
	if (!colors_split)
		return (0);
	if (char_tab_len(colors_split) != 3)
		return (free_char_tab(colors_split), 0);
	i = 0;
	while (colors_split[i])
	{
		color_int = ft_atoi(colors_split[i]);
		if ((ft_strlen(colors_split[i]) > 4) || color_int < 0
			|| color_int > 255)
			return (free_char_tab(colors_split), 0);
		i++;
	}
	free_char_tab(colors_split);
	return (1);
}

int	verify_colors_syntax(char *colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (!ft_isdigit(colors[i]) && colors[i] != ',' && (colors[i] != '\n'
				&& !colors[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	is_string_float(char *str)
{
	int i;

	if (!ft_strchr(str, '.'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}