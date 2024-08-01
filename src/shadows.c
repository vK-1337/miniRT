/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:43:44 by vk                #+#    #+#             */
/*   Updated: 2024/08/01 04:47:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_is_shadowed(t_world *world, t_tuple point)
{
	t_shadowed_norme	vars;

	vars.curr = *world->light;
	while (vars.curr)
	{
		vars.v = ft_dif_tuple(vars.curr->position, point);
		vars.distance = ft_magnitude(vars.v);
		vars.direction = ft_normalization(vars.v);
		vars.r = ft_ray(point, vars.direction);
		vars.intersections = ft_intersect_world(vars.r, &world);
		if (!vars.intersections)
			return (0);
		vars.hit = ft_hit(vars.intersections, vars.intersections->count);
		if (vars.hit && vars.hit->t && vars.hit->t < vars.distance)
			return (free(vars.intersections), 1);
		else
		{
			free(vars.intersections);
			if (vars.curr->next)
				vars.curr = vars.curr->next;
			else
				break ;
		}
	}
	return (0);
}
