/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:31:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:32:04 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

int	ft_init_all_light_values(char **data_split, t_light *light)
{
	char	**split;
	float	intensity;

	split = ft_split(data_split[1], ',');
	if (!split)
		return (free(light), 0);
	ft_init_light_pos(light, split);
	intensity = ft_atof(data_split[2]);
	split = ft_split(data_split[3], ',');
	if (!split)
		return (free(light), 0);
	ft_init_light_intensity(light, split, intensity);
	return (1);
}
