/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/20 17:36:26 by vda-conc         ###   ########.fr       */
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
        free(file_data);
        file_data = get_next_line(fd);
        if (file_data && file_data[0] == '\n')
          continue;
        if (init_corresponding_data(file_data, &data) == 2)
        {
          free(file_data);
          exit(EXIT_FAILURE);
        }
    }
	return (data);
}

int init_corresponding_data(char *file_data, t_data *data)
{
    char **data_split;
    t_dtype type;

    if (!file_data)
        return EXIT_FAILURE;
    data_split = ft_split(file_data, ' ');
    if (!data_split)
      return (2);
    type = determine_type(data_split[0]);
    if (!type || !verified_content(data_split, type)) // TODO Verified Content
    {
      free(data_split);
      write(STDERR_FILENO, ".rt file content is not valid.", 30);
      return (2);
    }
    init_data_w_line(data, type, data_split); // Possible de mettre cette fonction dans le if pour free si jamais un split casse dans les init;
    free(data_split);
    return EXIT_SUCCESS;
}

void init_data_w_line(t_data *data, t_dtype type, char **data_split)
{
  if (type == A)
    init_alight(data, data_split);
  else if (type == C)
    init_camera(data, data_split);
  else if (type == L)
    init_light(data, data_split);
  else if (type == PL)
    init_plan(data, data_split);
  else if (type == SP)
    init_sphere(data, data_split);
  else if (type == CY)
    init_cylindre(data, data_split);
}

void init_alight(t_data *data, char** data_split)
{
    char **color_split;

    data->alight->alight = ft_atof(data_split[1]);
    color_split = ft_split(data_split[2], ',');
    if (!color_split)
        return;
    data->alight->color_r = ft_atoi(color_split[0]);
    data->alight->color_g = ft_atoi(color_split[1]);
    data->alight->color_b = ft_atoi(color_split[2]);
    free_char_tab(color_split);
    return;
}

void init_camera(t_data *data, char** data_split)
{
    char **split;

    split = ft_split(data_split[1], ',');
    if (!split)
        return;
    data->camera->coord_x = atof(split[0]);
    data->camera->coord_y = atof(split[1]);
    data->camera->coord_z = atof(split[2]);
    free_char_tab(split);
    split = ft_split(data_split[2], ',');
    if (!split)
        return;
    data->camera->vector_x = atof(split[0]);
    data->camera->vector_y = atof(split[1]);
    data->camera->vector_z = atof(split[2]);
    data->camera->fov = atoi(data_split[3]);
    free_char_tab(split);
    return;
}

void init_light(t_data *data, char** data_split)
{
    char **split;

    split = ft_split(data_split[1], ',');
    if (!split)
        return;
    data->light->coord_x = atof(split[0]);
    data->light->coord_y = atof(split[1]);
    data->light->coord_z = atof(split[2]);
    free_char_tab(split);
    data->light->light_ratio = atof(data_split[2]);
    split = ft_split(data_split[3], ',');
    if (!split)
        return;
    data->alight->color_r = ft_atoi(split[0]);
    data->alight->color_g = ft_atoi(split[1]);
    data->alight->color_b = ft_atoi(split[2]);
    free_char_tab(split);
    return;
}

void init_sphere(t_data *data, char** data_split)
{
    char **split;

    split = ft_split(data_split[1], ',');
    if (!split)
        return;
    data->sphere->coord_x = atof(split[0]);
    data->sphere->coord_y = atof(split[1]);
    data->sphere->coord_z = atof(split[2]);
    free_char_tab(split);
    data->sphere->diameter = atof(data_split[2]);
    split = ft_split(data_split[3], ',');
    if (!split)
        return;
    data->sphere->color_r = ft_atoi(split[0]);
    data->sphere->color_g = ft_atoi(split[1]);
    data->sphere->color_b = ft_atoi(split[2]);
    free_char_tab(split);
    return;
}

void init_plan(t_data *data, char** data_split)
{
    char **split;

    split = ft_split(data_split[1], ',');
    if (!split)
        return;
    data->plan->coord_x = atof(split[0]);
    data->plan->coord_y = atof(split[1]);
    data->plan->coord_z = atof(split[2]);
    free_char_tab(split);
    split = ft_split(data_split[2], ',');
    if (!split)
        return;
    data->camera->vector_x = atof(split[0]);
    data->camera->vector_y = atof(split[1]);
    data->camera->vector_z = atof(split[2]);
    free_char_tab(split);
    split = ft_split(data_split[3], ',');
    if (!split)
        return;
    data->sphere->color_r = ft_atoi(split[0]);
    data->sphere->color_g = ft_atoi(split[1]);
    data->sphere->color_b = ft_atoi(split[2]);
    free_char_tab(split);
}


void init_cylindre(t_data *data, char** data_split)
{
    char **split;

    split = ft_split(data_split[1], ',');
    if (!split)
        return;
    data->cylindre->coord_x = atof(split[0]);
    data->cylindre->coord_y = atof(split[1]);
    data->cylindre->coord_z = atof(split[2]);
    free_char_tab(split);
    split = ft_split(data_split[2], ',');
    if (!split)
        return;
    data->cylindre->n_vector_x = atof(split[0]);
    data->cylindre->n_vector_y = atof(split[1]);
    data->cylindre->n_vector_z = atof(split[2]);
    data->cylindre->diameter = atof(data_split[3]);
    data->cylindre->height = atof(data_split[4]);
    free_char_tab(split);
    split = ft_split(data_split[3], ',');
    if (!split)
        return;
    data->sphere->color_r = ft_atoi(split[0]);
    data->sphere->color_g = ft_atoi(split[1]);
    data->sphere->color_b = ft_atoi(split[2]);
    free_char_tab(split);
}

t_dtype determine_type(char *data)
{
  if (strlen(data) > 2 || strlen(data) <= 0)
    return NOTYPE;
  if (strlen(data) == 1)
  {
    if (data[0] == 'A')
      return A;
    else if (data[0] == 'C')
      return C;
    else if (data[0] == 'L')
      return C;
  }
  else
  {
    if (data[0] == 'p' && data[1] == 'l')
      return PL;
    else if (data[0] == 's' && data[1] == 'p')
      return SP;
    if (data[0] == 'c' && data[1] == 'y')
      return CY;
  }
  return NOTYPE;
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
