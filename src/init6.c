/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:30:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:31:03 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_sphere(t_world *data, char **data_split, t_win *mlx)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	if (!ft_init_sphere_helper(data_split, sphere, mlx))
		return (0);
	if (data_split[4])
	{
		if (!ft_init_text_or_patt_sphere(data_split, sphere, mlx))
			return (0);
	}
	sphere->m->type = Sphere;
	if (data->alight != NULL)
	{
		sphere->m->ambiant_color = data->alight;
		sphere->m->ambiant = data->alight_intensity;
	}
	sphere->next = NULL;
	if (!add_sphere_to_lst(data, sphere))
		return (0);
	return (1);
}

int	ft_init_sphere_helper(char **data_split, t_sphere *sphere, t_win *mlx)
{
	char	**split;

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
		return (free_char_tab(split), free_sphere(&sphere, mlx), 0);
	init_m_color(sphere->m, split);
	return (1);
}

int	add_sphere_to_lst(t_world *data, t_sphere *sphere)
{
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

int	add_cylinder_to_lst(t_world *data, t_cylinder *cylinder)
{
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

int	add_plan_to_lst(t_world *data, t_plan *plan)
{
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
