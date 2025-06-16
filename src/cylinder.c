/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:02:29 by bainur            #+#    #+#             */
/*   Updated: 2024/07/31 09:31:55 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_cylinder_intersect(t_intersection **t_tab, t_cylinder **cylinder,
		t_ray ray, int *count)
{
	t_norme_cylinder	v;

	if (*cylinder == NULL)
		return ;
	v.new_ray = ray_transform(ray, ft_inversion((*cylinder)->matrix, 4));
	v.tab[0] = pow(v.new_ray.direction.x, 2) + pow(v.new_ray.direction.z, 2);
	if (fabsf(v.tab[0]) < EPSILON)
		return ;
	v.tab[1] = 2 * v.new_ray.origin.x * v.new_ray.direction.x + 2
		* v.new_ray.origin.z * v.new_ray.direction.z;
	v.tab[2] = pow(v.new_ray.origin.x, 2) + pow(v.new_ray.origin.z, 2)
		- pow((*cylinder)->radius, 2);
	v.tab[3] = pow(v.tab[1], 2) - 4 * v.tab[0] * v.tab[2];
	if (v.tab[3] < 0)
		return ;
	cylinder_intersect_helper(&v, cylinder, count, t_tab);
	v.t.t = (-v.tab[1] + sqrt(v.tab[3])) / (2 * v.tab[0]);
	v.y0 = v.new_ray.origin.y + v.t.t * v.new_ray.direction.y;
	if ((*cylinder)->y_min < v.y0 && v.y0 < (*cylinder)->y_max)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, v.t, *count);
	}
}

void	cylinder_intersect_helper(t_norme_cylinder *v, t_cylinder **cylinder,
		int *count, t_intersection **t_tab)
{
	v->t.t = (-v->tab[1] - sqrt(v->tab[3])) / (2 * v->tab[0]);
	v->t.cylinder = *cylinder;
	v->t.plan = NULL;
	v->t.sphere = NULL;
	v->t.cone = NULL;
	v->y0 = v->new_ray.origin.y + v->t.t * v->new_ray.direction.y;
	if ((*cylinder)->y_min < v->y0 && v->y0 < (*cylinder)->y_max)
	{
		*count += 1;
		*t_tab = ft_add_one_t(t_tab, v->t, *count);
	}
}

int	ft_check_caps(t_ray ray, float t, float radius)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if (fabsf(x * x + z * z) > radius * radius)
		return (0);
	else
		return (1);
}

void	ft_cylinder_caps_intersect(t_intersection **t_tab,
		t_cylinder **cylinder, t_ray ray, int *count)
{
	t_norme_caps_cylinder	v;

	if (!*cylinder)
		return ;
	v.new_ray = ray_transform(ray, ft_inversion((*cylinder)->matrix, 4));
	if (fabsf(v.new_ray.direction.y) < EPSILON)
	{
		*cylinder = (*cylinder)->next;
		return ;
	}
	v.t0 = ((*cylinder)->y_min - v.new_ray.origin.y) / v.new_ray.direction.y;
	if (ft_check_caps(v.new_ray, v.t0, (*cylinder)->radius))
	{
		cylinder_caps_helper(&v.t, count, *cylinder, v.t0);
		*t_tab = ft_add_one_t(t_tab, v.t, *count);
	}
	v.t1 = ((*cylinder)->y_max - v.new_ray.origin.y) / v.new_ray.direction.y;
	if (ft_check_caps(v.new_ray, v.t1, (*cylinder)->radius))
	{
		cylinder_caps_helper(&v.t, count, *cylinder, v.t1);
		*t_tab = ft_add_one_t(t_tab, v.t, *count);
	}
	*cylinder = (*cylinder)->next;
}

void	cylinder_caps_helper(t_intersection *t, int *count,
		t_cylinder *cylinder, float t_n)
{
	t->status = 1;
	t->t = t_n;
	t->cylinder = cylinder;
	t->plan = NULL;
	t->sphere = NULL;
	t->cone = NULL;
	*count += 1;
}
