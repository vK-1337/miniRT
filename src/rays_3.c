/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:40:05 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/29 18:40:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersection	ft_intersection(float t, t_sphere *sphere)
{
	t_intersection	i;

	i.t = t;
	i.sphere = sphere;
	return (i);
}

t_intersection	*ft_intersections_tab(int count, ...)
{
	int				i;
	va_list			args;
	t_intersection	*intersections;

	intersections = malloc(sizeof(t_intersection) * count);
	if (!intersections)
		return (NULL);
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		intersections[i] = va_arg(args, t_intersection);
		i++;
	}
	ft_sort_intersections(intersections, count);
	va_end(args);
	return (intersections);
}
