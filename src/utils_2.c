/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:03:27 by vda-conc          #+#    #+#             */
/*   Updated: 2024/08/22 12:45:20 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_sphere(t_sphere **sphere, void *mlx)
{
	t_sphere	*tmp;

	tmp = *sphere;
	while (*sphere)
	{
		tmp = (*sphere)->next;
		free_material((*sphere)->m, mlx);
		ft_free_mat((*sphere)->matrix, 4);
		free(*sphere);
		*sphere = tmp;
	}
	return ;
}

void	free_cylinder(t_cylinder **cylinder, void *mlx)
{
	t_cylinder	*tmp;

	tmp = *cylinder;
	while (*cylinder)
	{
		tmp = (*cylinder)->next;
		free_material((*cylinder)->m, mlx);
		ft_free_mat((*cylinder)->matrix, 4);
		free(*cylinder);
		*cylinder = tmp;
	}
	free(cylinder);
	return ;
}

void	free_cone(t_cone **cone, void *mlx)
{
	t_cone	*tmp;

	tmp = *cone;
	while (*cone)
	{
		tmp = (*cone)->next;
		free_material((*cone)->m, mlx);
		ft_free_mat((*cone)->matrix, 4);
		free(*cone);
		*cone = tmp;
	}
	free(cone);
	return ;
}

void	free_data(t_world **data, void *mlx)
{
	if ((*data)->alight)
		free((*data)->alight);
	if ((*data)->camera)
	{
		ft_free_mat((*data)->camera->matrix, 4);
		free((*data)->camera);
	}
	if ((*data)->light)
		free_light((*data)->light);
	if ((*data)->plan)
	{
		free_plan((*data)->plan, mlx);
		free((*data)->plan);
	}
	if ((*data)->sphere)
	{
		free_sphere((*data)->sphere, mlx);
		free((*data)->sphere);
	}
	if ((*data)->cylinder)
		free_cylinder((*data)->cylinder, mlx);
	if ((*data)->cone)
		free_cone((*data)->cone, mlx);
	free(*data);
	return ;
}
