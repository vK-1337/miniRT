/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/19 19:38:36 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	init_all_data(int fd)
{
	t_data	data;
	char	*file_data;

	null_data(&data);
    file_data = get_next_line(fd);
    if (file_data == NULL)
    {
        write(STDERR_FILENO, "The file is empty\n", 19);
        exit(EXIT_FAILURE);
    }
    init_corresponding_data(file_data, &data);
    while (file_data)
    {
        file_data = get_next_line(fd);
        init_corresponding_data(file_data, &data);
    }
	return (data);
}

void init_corresponding_data(char *file_data, t_data *data)
{
    char *data_split;

    if (!file_data)
        return;
    data_split = ft_split(file_data, ' ');
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
