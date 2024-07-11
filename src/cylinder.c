/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:02:29 by bainur            #+#    #+#             */
/*   Updated: 2024/07/11 13:01:35 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_cylinder_intersect(t_intersection **t_tab, t_cylinder **cylinder, t_ray ray, int *count)
{
    float tab[4];
    t_intersection t;
    t_ray new_ray;
    float y0;

    if (*cylinder == NULL)
        return;
    new_ray = ray_transform(ray, ft_inversion((*cylinder)->matrix, 4));
    tab[0] = pow(new_ray.direction.x, 2) + pow(new_ray.direction.z, 2);
    if (fabsf(tab[0]) < EPSILON)
        return;
    tab[1] = 2 * new_ray.origin.x * new_ray.direction.x + 2 * new_ray.origin.z * new_ray.direction.z;
    tab[2] = pow(new_ray.origin.x, 2) + pow(new_ray.origin.z, 2) - pow((*cylinder)->radius, 2);
    tab[3] = pow(tab[1], 2) - 4 * tab[0] * tab[2];
    if (tab[3] < 0)
        return;
    t.t = (-tab[1] - sqrt(tab[3])) / (2 * tab[0]);
    t.cylinder = *cylinder;
    t.plan = NULL;
    t.sphere = NULL;
    t.cone = NULL;
    y0 = new_ray.origin.y + t.t * new_ray.direction.y;
    if ((*cylinder)->y_min < y0 && y0 < (*cylinder)->y_max)
    {
        *count += 1;
        *t_tab = ft_add_one_t(t_tab, t, *count);
    }
    t.t = (-tab[1] + sqrt(tab[3])) / (2 * tab[0]);
    y0 = new_ray.origin.y + t.t * new_ray.direction.y;
    if ((*cylinder)->y_min < y0 && y0 < (*cylinder)->y_max)
    {
        *count += 1;
        *t_tab = ft_add_one_t(t_tab, t, *count);
    }
}

int ft_check_caps(t_ray ray, float t, float radius)
{
    float x;
    float z;

    x = ray.origin.x + t * ray.direction.x;
    z = ray.origin.z + t * ray.direction.z;
    if (fabsf(x * x + z * z) > radius * radius)
        return (0);
    else
        return (1);
}

void ft_cylinder_caps_intersect(t_intersection **t_tab, t_cylinder **cylinder, t_ray ray, int *count)
{
    t_intersection t;
    t_ray new_ray;
    float t0;
    float t1;

    if (!*cylinder)
        return;
    new_ray = ray_transform(ray, ft_inversion((*cylinder)->matrix, 4));
    if (fabsf(new_ray.direction.y) < EPSILON)
    {
        *cylinder = (*cylinder)->next;
        return;
    }
    t0 = ((*cylinder)->y_min - new_ray.origin.y) / new_ray.direction.y;
    if (ft_check_caps(new_ray, t0, (*cylinder)->radius))
    {
        t.t = t0;
        t.cylinder = *cylinder;
        t.plan = NULL;
        t.sphere = NULL;
        t.cone = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(t_tab, t, *count);
    }
    t1 = ((*cylinder)->y_max - new_ray.origin.y) / new_ray.direction.y;
    if (ft_check_caps(new_ray, t1, (*cylinder)->radius))
    {
        t.t = t1;
        t.cylinder = *cylinder;
        t.plan = NULL;
        t.sphere = NULL;
        t.cone = NULL;
        *count += 1;
        *t_tab = ft_add_one_t(t_tab, t, *count);
    }
    *cylinder = (*cylinder)->next;
}

t_cylinder *ft_cylinder(void)
{
    t_cylinder *cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    cylinder->radius = 1;
    cylinder->y_min = 0;
    cylinder->y_max = 3;
    cylinder->matrix = identity_matrix(4);
    cylinder->material = ft_material();
    cylinder->next = NULL;
    return (cylinder);
}