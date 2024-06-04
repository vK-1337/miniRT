/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:10 by udumas            #+#    #+#             */
/*   Updated: 2024/06/04 23:48:23 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void    ft_plan_intersect(t_intersection **t_tab, t_plan **plan, t_ray ray, int *count)
{
    t_intersection *new_t_tab;
    int i;

    i = 0;
    if (!*plan)
        return ;
    if (fabsf(ray.direction.y) < EPSILON)
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
    new_t_tab[i].t = -ray.origin.y / ray.direction.y;
    if ((*plan)->type == 1)
        printf("plan1 i = %f\n", new_t_tab[i].t);
    if ((*plan)->type == 2)
        printf("plan2 i = %f\n", new_t_tab[i].t);
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
    plan->colors = *ft_color(0.5, 0.5, 0.5);
    plan->coord = *ft_init_tuple(0, 0, 0, 1);
    plan->normal = *ft_init_tuple(1, 0, 0, 0);
    plan->material = ft_material();
    plan->matrix = identity_matrix(4);
    plan->next = NULL;
    return (plan);
}