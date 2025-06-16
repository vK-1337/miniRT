/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:59:31 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:10:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
		vect = ft_atof(vect_split[i]);
		if (vect > 1.0 || vect < -1.0)
			return (free_char_tab(vect_split), 0);
		i++;
	}
	free_char_tab(vect_split);
	return (1);
}

int	check_vect_syntax(char *data)
{
	int	i;

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
		else if (ft_isdigit(data[i]) && data[i] != '1' && data[i] != '0'
			&& data[i - 1] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	verify_coord(char *data)
{
	char	**coord_split;

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

int	check_coord_syntax(char *data)
{
	int	i;

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
	float_data = ft_atof(data[2]);
	if (float_data < 0.0 || float_data > 1.0)
		return (0);
	if (!verify_colors(data[3]))
		return (0);
	return (1);
}
