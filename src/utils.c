/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:45:44 by vk                #+#    #+#             */
/*   Updated: 2024/05/31 11:01:02 by vk               ###   ########.fr       */
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
	if (data->cylindre)
		cylindre_lstfree(data->cylindre);
	return ;
}
