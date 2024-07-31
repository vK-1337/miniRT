/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:29:56 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 22:01:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_plan(t_world *data, char **data_split, t_win *mlx)
{
	char	**split;
	t_plan	*plan;

	plan = malloc(sizeof(t_plan));
	if (!plan)
		return (0);
	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(plan), 0);
	if (!ft_init_plan_helper(data_split, plan))
		return (0);
    free_char_tab(split);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(plan), 0);
	plan->m = ft_material();
	if (!plan->m)
		return (free(plan), free_char_tab(split), 0);
	init_m_color(plan->m, split);
	plan->next = NULL;
	if (!ft_init_plan_helper2(data, data_split, plan, mlx))
		return (0);
	return (1);
}

int	ft_init_plan_helper2(t_world *data, char **data_split, t_plan *plan,
		void *mlx)
{
	if (data_split[4])
	{
		if (!ft_init_text_or_patt_plan(data_split, plan, mlx))
			return (0);
	}
	plan->m->type = Plan;
	if (data->alight != NULL)
	{
		plan->m->ambiant_color = data->alight;
		plan->m->ambiant = data->alight_intensity;
	}
	if (!add_plan_to_lst(data, plan))
		return (0);
	return (1);
}

int	ft_init_plan_helper(char **data_split, t_plan *plan)
{
	char	**split;
	float	**matrix;

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
	return (free_char_tab(split), 1);
}

int	ft_init_plan_pattern(char **split, t_plan *plan)
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
	plan->m->pattern = ft_pattern(v.p_color_1, v.p_color_2);
	plan->m->is_pattern = 1;
	if (!plan->m->pattern)
		return (free_char_tab(v.col_split), free(v.p_color_1),
			free(v.p_color_2), 0);
	return (free_char_tab(v.first_color), free_char_tab(v.second_color), 1);
}

int	ft_init_text_or_patt_plan(char **data_split, t_plan *plan, t_win *mlx)
{
	char	**split;

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
		if (!ft_init_plan_pattern(split, plan))
			return (free(plan), free_char_tab(split), 0);
	}
	free_char_tab(split);
	return (1);
}
