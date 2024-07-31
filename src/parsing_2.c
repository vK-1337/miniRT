/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:58:07 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 11:01:26 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	verify_cylinder(char **data)
{
	if (char_tab_len(data) != 6 && char_tab_len(data) != 7)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!is_string_float(data[3]) || !is_string_float(data[4]))
		return (0);
	if (!verify_colors(data[5]))
		return (0);
	if (data[6] && !verify_texture_and_pattern(data[6]))
		return (0);
	return (1);
}

int	verify_cone(char **data)
{
	if (char_tab_len(data) != 6 && char_tab_len(data) != 7)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!is_string_float(data[3]) || !is_string_float(data[4]))
		return (0);
	if (!verify_colors(data[5]))
		return (0);
	if (data[6] && !verify_texture_and_pattern(data[6]))
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
	int	i;

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
