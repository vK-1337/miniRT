/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/19 19:43:22 by vda-conc         ###   ########.fr       */
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
    float x;
    float y;
    float z;
    int orientation_v;
    int fov;
} t_camera;

typedef struct s_light
{
    float x;
    float y;
    float z;
    float light_ratio;
    int color_r;
    int color_g;
    int color_b;
} t_light;

typedef struct s_sphere
{
    float x;
    float y;
    float z;
    float diameter;
    int color_r;
    int color_g;
    int color_b;
} t_sphere;

typedef struct s_plan
{
    float x;
    float y;
    float z;
    int orientation_v;
    int color_r;
    int color_g;
    int color_b;
} t_plan;

typedef struct s_cylindre
{
    float x;
    float y;
    float z;
    int normal_v;
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

#endif