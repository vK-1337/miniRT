/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:43:44 by vk                #+#    #+#             */
/*   Updated: 2024/07/30 13:41:23 by vda-conc         ###   ########.fr       */
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
		free(vars.intersections);
		if (vars.hit && vars.hit->t < vars.distance)
			return (1);
		else
		{
			if (vars.curr->next)
				vars.curr = vars.curr->next;
			else
				break ;
		}
	}
	return (0);
}
