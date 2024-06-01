/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:43:44 by vk                #+#    #+#             */
/*   Updated: 2024/06/01 13:26:50 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int ft_is_shadowed(t_world *world, t_tuple point)
{
    t_tuple v;
    t_tuple direction;
    float distance;
    t_intersection *intersections;
    t_intersection *hit;

    v = ft_dif_tuple(world->light->position, point);
    distance = ft_magnitude(v);
    direction = ft_normalization(v);

    t_ray r = ft_ray(point, direction);
    intersections = ft_intersect_world(r, &world);

    hit = ft_hit(intersections, 2);
    if (hit && hit->t < distance)
    {
        free(hit);
        return (1);
    }
    free(hit);
    return (0);
}
