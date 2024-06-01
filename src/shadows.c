/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:43:44 by vk                #+#    #+#             */
/*   Updated: 2024/06/01 10:45:08 by vk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int ft_is_shadowed(t_world *world, t_tuple point)
{
    t_tuple v;
    t_tuple direction;
    float distance;
    float distance_to_light;
    t_list *curr;
    t_light *light;

    v = substract_tuple(world->light->position, point);
    direction = normalize_tuple(v);
    distance = magnitude(v);
    
    return (0);
}
