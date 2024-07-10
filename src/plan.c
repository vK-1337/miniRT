/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:10 by udumas            #+#    #+#             */
/*   Updated: 2024/07/10 15:54:14 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_intersection *ft_add_one_t(t_intersection **t_tab, t_intersection t, int count)
{
    t_intersection *new_t_tab;
	int i;

	i = 0;
    new_t_tab = malloc(sizeof(t_intersection) * (count));
    if (!new_t_tab)
        return (NULL);
    while (i < count - 1)
    {
        new_t_tab[i] = (*t_tab)[i];
        new_t_tab[i].status = 1;
        i++;
    }
    new_t_tab[i] = t;
    free(*t_tab);
    return (new_t_tab);
}
void ft_plan_intersect(t_intersection **t_tab, t_plan **plan, t_ray ray, int *count)
{
    t_ray new_ray;
    t_intersection *tmp;
    t_intersection t;
    
    if (!*plan)
        return ;
    tmp = *t_tab;
    new_ray = ray_transform(ray, ft_inversion((*plan)->matrix, 4));
    if (fabsf(new_ray.direction.y) < EPSILON)
    {
        *plan = (*plan)->next;
        return ;
    }
    t.status = 1;
    t.plan = *plan;
    t.sphere = NULL;
    t.cylinder = NULL;
    *count += 1;
    t.t = -new_ray.origin.y / new_ray.direction.y;
    *t_tab = ft_add_one_t(t_tab, t, *count);
    *plan = (*plan)->next;
}
t_plan *ft_plan(void)
{
    t_plan *plan;

    plan = malloc(sizeof(t_plan));
    plan->coord = *ft_init_tuple(0, 0, 0, 1);
    plan->normal = *ft_init_tuple(0, 1, 0, 0);
    plan->material = ft_material();
    plan->matrix = identity_matrix(4);
    plan->next = NULL;
    return (plan);
}