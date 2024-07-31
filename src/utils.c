/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:45:44 by vk                #+#    #+#             */
/*   Updated: 2024/07/31 19:36:03 by vda-conc         ###   ########.fr       */
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

void	free_light(t_light **light)
{
	t_light	*tmp;

	tmp = (*light);
	while (*light)
	{
		tmp = NULL;
		if ((*light)->next)
			tmp = (*light)->next;
		free(*light);
		*light = tmp;
	}
	free(light);
	return ;
}

void	free_plan(t_plan **plan, void *mlx)
{
	t_plan	*tmp;

	tmp = (*plan);
	while (*plan)
	{
		tmp = (*plan)->next;
		free_material((*plan)->m, mlx);
		ft_free_mat((*plan)->matrix, 4);
		free(*plan);
		*plan = tmp;
	}
	return ;
}

void	free_material(t_material *material, void *mlx)
{
	if (!material)
		return ;
	if (material->pattern)
	{
		free(material->pattern->a);
		free(material->pattern->b);
		ft_free_mat(material->pattern->transform, 4);
		free(material->pattern);
	}
	if (material->texture)
	{
		mlx_destroy_image(mlx, material->texture->img_ptr);
		free(material->texture);
	}
	free(material);
}
