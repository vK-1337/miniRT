/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:30:39 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:34:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	add_cone_to_lst(t_world *data, t_cone *cone)
{
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

int	ft_init_text_or_patt_sphere(char **data_split, t_sphere *sphere, t_win *mlx)
{
	char	**split;

	split = ft_split(data_split[4], ':');
	if (!split)
		return (free(sphere), 0);
	if (ft_strncmp(split[0], "texture", 8) == 0)
	{
		free(sphere->m);
		sphere->m = ft_texture(split[1], mlx);
		if (!sphere->m->texture)
			return (free_sphere(&sphere, mlx), free_char_tab(split), 0);
	}
	else if (ft_strncmp(split[0], "pattern", 8) == 0)
	{
		if (!ft_init_sphere_pattern(split, sphere))
			return (free_sphere(&sphere, mlx), free_char_tab(split), 0);
	}
	free_char_tab(split);
	return (1);
}

int	ft_init_text_or_patt_cyl(char **data_split, t_cylinder *cylinder,
		t_win *mlx)
{
	char	**split;

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
		if (!ft_init_cylinder_pattern(split, cylinder))
			return (free(cylinder), free_char_tab(split), 0);
	}
	free_char_tab(split);
	return (1);
}

int	ft_init_sphere_pattern(char **split, t_sphere *sphere)
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
	sphere->m->pattern = ft_pattern(v.p_color_1, v.p_color_2);
	sphere->m->is_pattern = 1;
	if (!sphere->m->pattern)
		return (free_char_tab(v.col_split), free(v.p_color_1),
			free(v.p_color_2), 0);
	return (free_char_tab(v.first_color), free_char_tab(v.second_color), 1);
}

int	ft_init_cylinder_pattern(char **split, t_cylinder *cylinder)
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
	cylinder->m->pattern = ft_pattern(v.p_color_1, v.p_color_2);
	cylinder->m->is_pattern = 1;
	if (!cylinder->m->pattern)
		return (free_char_tab(v.col_split), free(v.p_color_1),
			free(v.p_color_2), 0);
	return (free_char_tab(v.first_color), free_char_tab(v.second_color), 1);
}
