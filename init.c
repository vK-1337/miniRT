/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/19 18:55:12 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	init_all_data(int fd)
{
	t_data	data;
	char	*file_data;

	null_data(&data);
	return (data);
}

void	null_data(t_data *data)
{
	data->alight = NULL;
	data->camera = NULL;
	data->cylindre = NULL;
	data->light = NULL;
	data->plan = NULL;
	data->sphere = NULL;
	return ;
}
