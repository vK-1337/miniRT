/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:58:49 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 10:59:10 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	verify_texture_and_pattern(char *data)
{
	char	**data_split;

	data_split = ft_split(data, ':');
	if (!data_split)
		return (0);
	if (char_tab_len(data_split) != 2)
		return (free_char_tab(data_split), 0);
	if (ft_strncmp(data_split[0], "texture", 7) == 0)
		return (verify_texture(data_split[1], &data_split));
	else if (ft_strncmp(data_split[0], "pattern", 7) == 0)
		return (verify_pattern(data_split[1], &data_split));
	return (free_char_tab(data_split), 0);
}

int	verify_pattern(char *pattern, char ***upper_split)
{
	char	**data_split;

	data_split = ft_split(pattern, ';');
	if (!data_split)
		return (free_char_tab(*upper_split), 0);
	if (char_tab_len(data_split) != 2)
		return (free_char_tab(*upper_split), free_char_tab(data_split), 0);
	if (!verify_colors(data_split[0]) || !verify_colors(data_split[1]))
		return (free_char_tab(*upper_split), free_char_tab(data_split), 0);
	return (free_char_tab(*upper_split), free_char_tab(data_split), 1);
}

int	verify_texture(char *texture, char ***data_split)
{
	int	i;

	i = 0;
	while (texture[i])
		i++;
	if (i < 6)
		return (free_char_tab(*data_split), 0);
	if (texture[i - 2] != 'm' && texture[i - 3] != 'p' && texture[i - 4] != 'x')
		return (free_char_tab(*data_split), 0);
	if (texture[i - 5] != '.')
		return (free_char_tab(*data_split), 0);
	return (free_char_tab(*data_split), 1);
}

int	verify_sphere(char **data)
{
	if (char_tab_len(data) != 4 && char_tab_len(data) != 5)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!is_string_float(data[2]))
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	if (data[4] && !verify_texture_and_pattern(data[4]))
		return (0);
	return (1);
}

int	verify_plan(char **data)
{
	if (char_tab_len(data) != 4 && char_tab_len(data) != 5)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	if (data[4] && !verify_texture_and_pattern(data[4]))
		return (0);
	return (1);
}
