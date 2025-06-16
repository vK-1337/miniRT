/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:52 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:10:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	scene_name_check(char *av)
{
	int	i;

	if (!av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	if (i <= 1)
		return (0);
	if (av[i - 1] != 't' && av[i - 2] != 'r' && av[i - 3] != '.')
		return (0);
	if (!av[i - 4])
		return (0);
	return (1);
}

int	verified_content(char **data, t_dtype type)
{
	if (type == A)
		return (verify_alight(data));
	else if (type == C)
		return (verify_camera(data));
	else if (type == L)
		return (verify_light(data));
	else if (type == PL)
		return (verify_plan(data));
	else if (type == SP)
		return (verify_sphere(data));
	else if (type == CY)
		return (verify_cylinder(data));
	else if (type == CO)
		return (verify_cone(data));
	return (0);
}

int	verify_alight(char **data)
{
	int		i;
	float	float_data;

	i = 1;
	if (char_tab_len(data) != 3)
		return (0);
	while (data[i])
	{
		if (i == 1)
		{
			if (!is_string_float(data[i]))
				return (0);
			float_data = ft_atof(data[i]);
			if (float_data < 0.0 || float_data > 1.0)
				return (0);
		}
		else if (i == 2)
		{
			if (!verify_colors(data[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

int	verify_camera(char **data)
{
	if (char_tab_len(data) != 4)
		return (0);
	if (!verify_coord(data[1]))
		return (0);
	if (!verify_vect(data[2]))
		return (0);
	if (!verify_fov(data[3]))
		return (0);
	return (1);
}
