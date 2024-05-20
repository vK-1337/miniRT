/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:28:58 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/20 08:29:11 by vk               ###   ########.fr       */
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

void init_alight(t_data *data, char** data_split) // ! HERE
{
  char ** split_content;
  t_alight new_alight;
  new_alight.alight = data_split[1]; // Need to do atof
}

void init_camera(t_data *data, char** data_split)
{
  ;
}

void init_light(t_data *data, char** data_split)
{
  ;
}

void init_plan(t_data *data, char** data_split)
{
  ;
}

void init_sphere(t_data *data, char** data_split)
{
  ;
}

void init_cylindre(t_data *data, char** data_split)
{
  ;

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
