/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/24 15:11:26 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.00001
# define INFINITY 1e10
# define SIZE_X 1280
# define SIZE_Y 800
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <wait.h>

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
}					t_dtype;

typedef struct s_alight
{
	float			alight;
	int				color_r;
	int				color_g;
	int				color_b;
}					t_alight;

typedef struct s_camera
{
	float			coord_x;
	float			coord_y;
	float			coord_z;
	float			vector_x;
	float			vector_y;
	float			vector_z;
	int				fov;
}					t_camera;

typedef struct s_light
{
	float			coord_x;
	float			coord_y;
	float			coord_z;
	float			light_ratio;
	int				color_r;
	int				color_g;
	int				color_b;
}					t_light;

typedef struct s_sphere
{
	float			coord_x;
	float			coord_y;
	float			coord_z;
	float			diameter;
	int				color_r;
	int				color_g;
	int				color_b;
}					t_sphere;

typedef struct s_plan
{
	float			coord_x;
	float			coord_y;
	float			coord_z;
	float			vector_x;
	float			vector_y;
	float			vector_z;
	int				color_r;
	int				color_g;
	int				color_b;
}					t_plan;

typedef struct s_cylindre
{
	float			coord_x;
	float			coord_y;
	float			coord_z;
	float			n_vector_x;
	float			n_vector_y;
	float			n_vector_z;
	float			diameter;
	float			height;
	int				color_r;
	int				color_g;
	int				color_b;
}					t_cylindre;

typedef struct s_data
{
	t_alight		*alight;
	t_camera		*camera;
	t_light			*light;
	t_sphere		*sphere;
	t_plan			*plan;
	t_cylindre		*cylindre;
}					t_data;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_tuple;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_win;

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PARSING                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int					scene_name_check(char *av);
t_data				init_all_data(int fd);
void				null_data(t_data *data);
int					init_corresponding_data(char *file_data, t_data *data);
void				init_data_w_line(t_data *data);
t_dtype				determine_type(char *data);
int					char_tab_len(char **tab);
void				free_char_tab(char **tab);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   TUPLE_CALCULATION                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_tuple				ft_sum_tuple(t_tuple t1, t_tuple t2);
t_tuple				ft_dif_tuple(t_tuple t1, t_tuple t2);
t_tuple				ft_neg_tuple(t_tuple t);
t_tuple				ft_mult_vector(t_tuple v, float scale);
t_tuple				ft_div_vector(t_tuple v, int scale);
int					ft_comp_float(float n1, float n2);
int					same_tuple(t_tuple t1, t_tuple t2);
float				ft_magnitude(t_tuple v);
t_tuple				ft_normalization(t_tuple v);
float				ft_dotproduct(t_tuple v1, t_tuple v2);
t_tuple				cross_product(t_tuple v1, t_tuple v2);

//										COLORS									//

t_color				ft_sum_color(t_color c1, t_color c2);
t_color				ft_dif_color(t_color c1, t_color c2);
t_color				ft_mult_color(t_color c, int scalar);
t_color				ft_mult_color_tog(t_color c1, t_color c2);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   MATRICE                        		  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

float	**ft_matcre(float *tab, int row_col);
void	ft_mult_mat(float res[4][4], float mat1[4][4], float mat2[4][4]);
void	ft_mult_mat_tuple(float tuple[4], float mat[4][4]);

#endif
