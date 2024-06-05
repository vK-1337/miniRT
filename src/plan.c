/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:10 by udumas            #+#    #+#             */
/*   Updated: 2024/06/05 15:15:29 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void ft_plan_intersect(t_intersection **t_tab, t_plan **plan, t_ray ray, int *count)
{
    t_intersection *new_t_tab;
    int i;

    i = 0;
    if (!*plan)
        return ;

    float denominator = ft_dotproduct(ray.direction, (*plan)->normal);
    if (fabsf(denominator) < EPSILON)
    {
        *plan = (*plan)->next;
        return ;
    }

    *count += 1;
    new_t_tab = malloc(sizeof(t_intersection) * (*count));
    while (i < *count - 1)
    {
        new_t_tab[i] = (*t_tab)[i];
        new_t_tab[i].status = 1;
        i++;
    }

    new_t_tab[i].status = 1;
    new_t_tab[i].t = ft_dotproduct(ft_dif_tuple((*plan)->coord, ray.origin), (*plan)->normal) / denominator;
    new_t_tab[i].plan = *plan;
    new_t_tab[i].sphere = NULL;
    *plan = (*plan)->next;
    free(*t_tab);
    *t_tab = new_t_tab;
}
t_plan *plan1(void)
{
    t_plan *plan;

    plan = malloc(sizeof(t_plan));
    plan->coord = *ft_init_tuple(0, 0, 0, 1);
    plan->normal = *ft_init_tuple(0, 0, 0, 0);
    plan->material = ft_material();
    plan->matrix = identity_matrix(4);
    plan->next = NULL;
    return (plan);
}