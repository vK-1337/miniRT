/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/20 19:42:30 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "./gnl/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                              STRUCT & ENUM                                 */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

typedef enum e_dtype
{
    NOTYPE,
    A,
    C,
    L,
    SP,
    PL,
    CY
}   t_dtype;

typedef struct s_alight
{
    float alight;
    int color_r;
    int color_g;
    int color_b;
} t_alight;

typedef struct s_camera
{
    float coord_x;
    float coord_y;
    float coord_z;
    float vector_x;
    float vector_y;
    float vector_z;
    int fov;
} t_camera;

typedef struct s_light
{
    float coord_x;
    float coord_y;
    float coord_z;
    float light_ratio;
    int color_r;
    int color_g;
    int color_b;
} t_light;

typedef struct s_sphere
{
    float coord_x;
    float coord_y;
    float coord_z;
    float diameter;
    int color_r;
    int color_g;
    int color_b;
} t_sphere;

typedef struct s_plan
{
    float coord_x;
    float coord_y;
    float coord_z;
    float vector_x;
    float vector_y;
    float vector_z;
    int color_r;
    int color_g;
    int color_b;
} t_plan;

typedef struct s_cylindre
{
    float coord_x;
    float coord_y;
    float coord_z;
    float n_vector_x;
    float n_vector_y;
    float n_vector_z;
    float diameter;
    float height;
    int color_r;
    int color_g;
    int color_b;
} t_cylindre;

typedef struct s_data
{
    t_alight *alight;
    t_camera *camera;
    t_light *light;
    t_sphere *sphere;
    t_plan *plan;
    t_cylindre *cylindre;
}   t_data;

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PARSING                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int scene_name_check(char *av);
t_data init_all_data(int fd);
void	null_data(t_data *data);
int init_corresponding_data(char *file_data, t_data *data);
void init_data_w_line(t_data *data, t_dtype type, char **data_split);
t_dtype determine_type(char *data);
int char_tab_len(char **tab);
void free_char_tab(char **tab);
int is_string_float(char *str);
int verify_colors(char *str);
int verify_alight(char **data);
int verify_camera(char **data);
int verify_light(char **data);
int verify_plan(char **data);
int verify_sphere(char **data);
int verify_cylindre(char **data);
int verified_content(char **data, t_dtype type);
int verify_coord(char *data);
int verify_vect(char *data);
int verify_fov(char *data);
int	check_fov_syntax(char *data);
int check_vect_syntax(char *data);
int check_coord_syntax(char *data);
int verify_colors_syntax(char *data);
void init_alight(t_data *data, char** data_split);
void init_camera(t_data *data, char** data_split);
void init_light(t_data *data, char** data_split);
void init_sphere(t_data *data, char** data_split);
void init_plan(t_data *data, char** data_split);
void init_cylindre(t_data *data, char** data_split);
t_dtype determine_type(char *data);
void	null_data(t_data *data);
void print_all_data(t_data data);
#endif
