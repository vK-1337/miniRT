/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:21 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 11:00:32 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	verify_fov(char *data)
{
	int	fov;

	if (!data || !check_fov_syntax(data))
		return (0);
	fov = ft_atoi(data);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

int	check_fov_syntax(char *data)
{
	int	i;

	if (!data || (ft_strlen(data) > 3 && data[ft_strlen(data) - 1] != '\n'))
		return (0);
	i = 0;
	while (data[i])
	{
		if (!ft_isdigit(data[i]) && (data[i] != '\n' && !data[i + 1]))
			return (0);
		i++;
	}
	return (1);
}
