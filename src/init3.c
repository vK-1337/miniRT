/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:28:38 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:29:00 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_cylinder(t_world *data, char **data_split, t_win *mlx)
{
	char		**split;
	t_cylinder	*cylinder;
	int			y;

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
	if (!ft_init_cylinder_helper(data_split, cylinder, y))
		return (0);
	cylinder->next = NULL;
	if (ft_init_cylinder_helper2(cylinder, data, data_split, mlx) == 0)
		return (0);
	if (!add_cylinder_to_lst(data, cylinder))
		return (0);
	return (1);
}

int	ft_init_cylinder_helper2(t_cylinder *cylinder, t_world *data,
		char **data_split, t_win *mlx)
{
	if (data->alight != NULL)
	{
		cylinder->m->ambiant_color = data->alight;
		cylinder->m->ambiant = data->alight_intensity;
	}
	if (data_split[6])
	{
		if (!ft_init_text_or_patt_cyl(data_split, cylinder, mlx))
			return (0);
	}
	cylinder->m->type = Cylinder;
	if (data->alight != NULL)
	{
		cylinder->m->ambiant_color = data->alight;
		cylinder->m->ambiant = data->alight_intensity;
	}
	return (1);
}

int	ft_init_cylinder_helper(char **data_split, t_cylinder *cylinder, int y)
{
	char	**split;

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
	if (!cylinder->m)
		return (free(cylinder), free_char_tab(split), 0);
	init_m_color(cylinder->m, split);
	return (1);
}

int	init_cone(t_world *data, char **data_split, t_win *mlx)
{
	char	**split;
	t_cone	*cone;
	int		y;

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
	if (!ft_init_cone_helper(data_split, cone, y))
		return (0);
	cone->next = NULL;
	if (!ft_init_cone_helper2(cone, data, data_split, mlx))
		return (0);
	if (!add_cone_to_lst(data, cone))
		return (0);
	return (1);
}

int	ft_init_cone_helper2(t_cone *cone, t_world *data, char **data_split,
		t_win *mlx)
{
	if (data_split[6])
	{
		if (!ft_init_text_or_patt_cone(data_split, cone, mlx))
			return (0);
	}
	cone->m->type = Cone;
	if (data->alight != NULL)
	{
		cone->m->ambiant_color = data->alight;
		cone->m->ambiant = data->alight_intensity;
	}
	return (1);
}
