/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:51:28 by bainur            #+#    #+#             */
/*   Updated: 2024/06/07 20:27:25 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_cone_intersect(t_intersection **t_tab, t_cone **cone, t_ray ray, int *count)
{
    float tab[4];
    t_intersection t;
    t_ray new_ray;

    if (*cone == NULL)
        return;
    new_ray = ray_transform(ray, ft_inversion((*cone)->matrix, 4));
    tab[0] = pow(new_ray.direction.x, 2) - pow(new_ray.direction.y, 2) + pow(new_ray.direction.z, 2);
    tab[1] = 2 * new_ray.origin.x * new_ray.direction.x - 2 * new_ray.origin.y * new_ray.direction.y + 2 * new_ray.origin.z * new_ray.direction.z;
    tab[2] = pow(new_ray.origin.x, 2) - pow(new_ray.origin.y, 2) + pow(new_ray.origin.z, 2);
    if (fabsf(tab[0]) < EPSILON && fabsf(tab[1]) < EPSILON)
    {
        *cone = (*cone)->next;
        return;
    }
    else if (fabsf(tab[0]) < EPSILON && fabsf(tab[1]) >= EPSILON)
    {
        t.t = -tab[2] / (2 * tab[1]);
        t.cone = *cone;
        t.plan = NULL;
        t.sphere = NULL;
        t.cylinder = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(*t_tab, t, *count);
        *cone = (*cone)->next;
        return;
    }
    tab[3] = pow(tab[1], 2) - 4 * tab[0] * tab[2];
    if (tab[3] < 0)
    {
        *cone = (*cone)->next;
        return;
    }
    t.t = (-tab[1] - sqrt(tab[3])) / (2 * tab[0]);
    t.cone = *cone;
    t.plan = NULL;
    t.sphere = NULL;
    t.cylinder = NULL;
    *count += 1;
    *t_tab = ft_add_one_t(*t_tab, t, *count);
    t.t = (-tab[1] + sqrt(tab[3])) / (2 * tab[0]);
    *count += 1;
    *t_tab = ft_add_one_t(*t_tab, t, *count);
    print_matrix(t.cone->matrix, 4);
    *cone = (*cone)->next;
}

t_cone *ft_cone(void)
{
    t_cone *cone;

    cone = malloc(sizeof(t_cone));
    if (!cone)
        return (NULL);
    cone->radius = 1;
    cone->matrix = identity_matrix(4);
    cone->material = ft_material();
    cone->next = NULL;
    return (cone);
}