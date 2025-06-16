/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:31:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:31:31 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light	*ft_init_light(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (0);
	light->next = NULL;
	light->position = (t_tuple){0, 0, 0, 1};
	light->intensity = (t_color){0, 0, 0, 0};
	light->colors = (t_color){0, 0, 0, 0};
	return (light);
}

void	ft_init_light_pos(t_light *light, char **split)
{
	light->position.x = ft_atof(split[0]);
	light->position.y = ft_atof(split[1]);
	light->position.z = ft_atof(split[2]);
	light->position.w = 1;
	free_char_tab(split);
}

void	ft_init_light_intensity(t_light *light, char **split, float intensity)
{
	light->intensity.r = ft_atoi(split[0]) / 255.0f * intensity;
	light->intensity.g = ft_atoi(split[1]) / 255.0f * intensity;
	light->intensity.b = ft_atoi(split[2]) / 255.0f * intensity;
	light->colors = ft_color_reg(light->intensity.r, light->intensity.g,
			light->intensity.b);
	free_char_tab(split);
}

int	init_light(t_world *data, char **data_split)
{
	t_light	*light;

	light = ft_init_light();
	if (!light)
		return (0);
	if (!ft_init_all_light_values(data_split, light))
		return (0);
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

void	init_m_color(t_material *m, char **split)
{
	m->color.r = ft_atoi(split[0]) / 255.0f;
	m->color.g = ft_atoi(split[1]) / 255.0f;
	m->color.b = ft_atoi(split[2]) / 255.0f;
	free_char_tab(split);
}
