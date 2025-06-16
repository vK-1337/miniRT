/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:28:06 by vda-conc          #+#    #+#             */
/*   Updated: 2024/08/22 12:55:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_init_cone_helper(char **data_split, t_cone *cone, int y)
{
	char	**split;

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
	if (!cone->m)
		return (free(cone), free_char_tab(split), 0);
	init_m_color(cone->m, split);
	return (1);
}

int	ft_init_text_or_patt_cone(char **data_split, t_cone *cone, t_win *mlx)
{
	char	**split;

	split = ft_split(data_split[6], ':');
	if (!split)
		return (free(cone), 0);
	if (ft_strncmp(split[0], "texture", 8) == 0)
	{
		free(cone->m);
		cone->m = ft_texture(split[1], mlx);
		if (!cone->m->texture)
			return (free(cone), free_char_tab(split), 0);
	}
	else if (ft_strncmp(split[0], "pattern", 8) == 0)
	{
		if (!ft_init_cone_pattern(split, cone))
			return (free(cone), free_char_tab(split), 0);
	}
	free_char_tab(split);
	return (1);
}

int	ft_init_cone_pattern(char **split, t_cone *cone)
{
	t_norme_init_pattern	v;

	v.col_split = ft_split(split[1], ';');
	if (!v.col_split)
		return (0);
	v.first_color = ft_split(v.col_split[0], ',');
	if (!v.first_color)
		return (free_char_tab(v.col_split), 0);
	v.p_color_1 = ft_color(ft_atoi(v.first_color[0]), ft_atoi(v.first_color[1]),
			ft_atoi(v.first_color[2]));
	if (!v.p_color_1)
		return (free_char_tab(v.col_split), free_char_tab(v.first_color), 0);
	v.second_color = ft_split(v.col_split[1], ',');
	free_char_tab(v.col_split);
	v.p_color_2 = ft_color(ft_atoi(v.second_color[0]),
			ft_atoi(v.second_color[1]), ft_atoi(v.second_color[2]));
	if (!v.p_color_2)
		return (free(v.p_color_1), free_char_tab(v.col_split),
			free_char_tab(v.first_color), 0);
	cone->m->pattern = ft_pattern(v.p_color_1, v.p_color_2);
	cone->m->is_pattern = 1;
	if (!cone->m->pattern)
		return (free_char_tab(v.col_split), free(v.p_color_1),
			free(v.p_color_2), 0);
	return (free_char_tab(v.first_color), free_char_tab(v.second_color), 1);
}

t_dtype	determine_type(char *data)
{
	if (!data || ft_strlen(data) > 2 || ft_strlen(data) <= 0)
		return (NOTYPE);
	if (ft_strlen(data) == 1)
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
