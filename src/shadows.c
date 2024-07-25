/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:43:44 by vk                #+#    #+#             */
/*   Updated: 2024/07/25 10:29:00 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_is_shadowed(t_world *world, t_tuple point)
{
	t_tuple			v;
	t_tuple			direction;
	float			distance;
	t_intersection	*intersections;
	t_intersection	*hit;
	t_ray			r;

	v = ft_dif_tuple(world->light->position, point);
	distance = ft_magnitude(v);
	direction = ft_normalization(v);
	r = ft_ray(point, direction);
	intersections = ft_intersect_world(r, &world);
	hit = ft_hit(intersections, intersections->count);
	if (hit && hit->t < distance)
	{
		free(intersections);
		return (1);
	}
    else
	{
		free(intersections);
	    return (0);
	}
}
