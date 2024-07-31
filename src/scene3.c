/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:30:20 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 13:30:56 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_comps	ft_null_comps(void)
{
	t_comps	comps;

	comps.t = 0;
	comps.sphere = NULL;
	comps.plan = NULL;
	comps.point = (t_tuple){0, 0, 0, 0};
	comps.eyev = (t_tuple){0, 0, 0, 0};
	comps.normalv = (t_tuple){0, 0, 0, 0};
	comps.over_point = (t_tuple){0, 0, 0, 0};
	comps.inside = 0;
	return (comps);
}

void	ft_sphere_comps(t_comps *comps, t_sphere *sphere)
{
	comps->sphere = sphere;
	comps->plan = NULL;
	comps->cylinder = NULL;
	comps->cone = NULL;
	comps->type = SPHERE;
}

void	ft_plan_comps(t_comps *comps, t_plan *plan)
{
	comps->plan = plan;
	comps->sphere = NULL;
	comps->cylinder = NULL;
	comps->cone = NULL;
	comps->type = PLAN;
}

void	ft_cylinder_comps(t_comps *comps, t_cylinder *cylinder)
{
	comps->cylinder = cylinder;
	comps->sphere = NULL;
	comps->plan = NULL;
	comps->cone = NULL;
	comps->type = CYLINDER;
}
