/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:45:44 by vk                #+#    #+#             */
/*   Updated: 2024/07/10 16:37:21 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

int	char_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void free_light(t_light *light)
{
	t_light	*tmp;

	tmp = light;
	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
	return ;
}	
void free_material(t_material *material)
{
	if (material->pattern)
		free(material->pattern);
	free(material);
}

void free_plan(t_plan **plan)
{
	t_plan	*tmp;

	tmp = (*plan);
	while (*plan)
	{
		tmp = (*plan)->next;
		free_material((*plan)->material);
		ft_free_mat((*plan)->matrix, 4);
		free(*plan);
		*plan = tmp;
	}
	return ;
}

void free_sphere(t_sphere **sphere)
{
	t_sphere	*tmp;

	tmp = *sphere;
	while (*sphere)
	{
		tmp = (*sphere)->next;
		free_material((*sphere)->material);
		ft_free_mat((*sphere)->matrix, 4);
		free(*sphere);
		*sphere = tmp;
	}
	return ;
}

void free_cylinder(t_cylinder **cylinder)
{
	t_cylinder	*tmp;

	tmp = *cylinder;
	while (*cylinder)
	{
		tmp = (*cylinder)->next;
		free_material((*cylinder)->material);
		ft_free_mat((*cylinder)->matrix, 4);
		free(*cylinder);
		*cylinder = tmp;
	}
	return ;
}

void free_cone(t_cone **cone)
{
	t_cone	*tmp;

	tmp = *cone;
	while (*cone)
	{
		tmp = (*cone)->next;
		free_material((*cone)->material);
		ft_free_mat((*cone)->matrix, 4);
		free(*cone);
		*cone = tmp;
	}
	return ;
}

void	free_data(t_world **data)
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
		free_plan((*data)->plan);
		free((*data)->plan);
	}
	if ((*data)->sphere)
	{
		free_sphere((*data)->sphere);
		free((*data)->sphere);
	}
	if ((*data)->cylinder)
	{
		free_cylinder((*data)->cylinder);
		free((*data)->cylinder);
	}
	if ((*data)->cone)
	{
		free_cone((*data)->cone);
		free((*data)->cone);
	}
	free(*data);
	return ;
}
