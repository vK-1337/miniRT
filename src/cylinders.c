/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:02:29 by bainur            #+#    #+#             */
/*   Updated: 2024/06/05 19:31:33 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_cylinder_intersect(t_intersection **t_tab, t_cylinder **cylinder, t_ray ray, int *count)
{
    float tab[4];
    t_intersection t[2];
    t_ray new_ray;

    if (*cylinder == NULL)
        return;
    new_ray = ray_transform(ray, ft_inversion((*cylinder)->matrix, 4));
    tab[0] = pow(new_ray.direction.x, 2) + pow(new_ray.direction.z, 2);
    if (fabsf(tab[0]) < EPSILON)
    {
        *cylinder = (*cylinder)->next;
        return;
    }
    tab[1] = 2 * new_ray.origin.x * new_ray.direction.x + 2 * new_ray.origin.z * new_ray.direction.z;
    tab[2] = pow(new_ray.origin.x, 2) + pow(new_ray.origin.z, 2) - pow((*cylinder)->radius, 2);
    tab[3] = pow(tab[1], 2) - 4 * tab[0] * tab[2];
    if (tab[3] < 0)
    {
        *cylinder = (*cylinder)->next;
        return;
    }
    t[0].t = (-tab[1] - sqrt(tab[3])) / (2 * tab[0]);
    t[0].cylinder = *cylinder;
    t[0].plan = NULL;
    t[0].sphere = NULL;
    t[1].t = (-tab[1] + sqrt(tab[3])) / (2 * tab[0]);
    t[1].cylinder = *cylinder;
    t[1].plan = NULL;
    t[0].sphere = NULL;
    *count += 2;
    *t_tab = ft_add_t(*t_tab, t, *count);
    *cylinder = (*cylinder)->next;

}

t_cylinder *cylinder(void)
{
    t_cylinder *cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    cylinder->radius = 1;
    cylinder->matrix = identity_matrix(4);
    cylinder->material = ft_material();
    cylinder->next = NULL;
    return (cylinder);
}