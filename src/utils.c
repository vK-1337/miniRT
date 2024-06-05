/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:45:44 by vk                #+#    #+#             */
/*   Updated: 2024/06/05 19:31:33 by bainur           ###   ########.fr       */
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

void	free_data(t_world *data)
{
	if (data->alight)
		free(data->alight);
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
	if (data->plan)
		plan_lstfree(data->plan);
	if (data->sphere)
		sphere_lstfree(data->sphere);
	if (data->cylinder)
		cylinder_lstfree(data->cylinder);
	return ;
}
