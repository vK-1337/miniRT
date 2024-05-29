/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/29 15:47:11 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define EPSILON 0.00001
# define INFINITY 1e10
# define SIZE_X 100
# define SIZE_Y 100
# define CENTER_X SIZE_X / 2
# define CENTER_Y SIZE_Y / 2
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
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
}						t_dtype;

typedef struct t_wall
{
	float				x;
	float				y;
	float				z;
	float				size;
}						t_wall;

typedef struct s_tuple
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_tuple;

typedef struct s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

typedef struct t_discriminant
{
	float				a;
	float				b;
	float				c;
	float				result;
}						t_discriminant;

typedef struct s_ray
{
	t_tuple				origin;
	t_tuple				direction;
}						t_ray;

typedef struct s_alight
{
	float				alight;
	t_color				colors;
}						t_alight;

typedef struct s_camera
{
	t_tuple				coord;
	t_tuple				vector;
	int					fov;
}						t_camera;

typedef struct s_light
{
	t_tuple				coord;
	float				light_ratio;
	t_color				colors;
}						t_light;

typedef struct s_sphere
{
	t_tuple				center;
	float				diameter;
	t_color				colors;
	struct s_sphere		*next;
	float				radius;
	int					id;
	float				**matrix;
}						t_sphere;

typedef struct s_intersection
{
	float				t;
	t_sphere			*object;
}						t_intersection;

typedef struct s_plan
{
	t_tuple				coord;
	t_tuple				vector;
	t_color				colors;
	struct s_plan		*next;
}						t_plan;

typedef struct s_cylindre
{
	t_tuple				coord;
	t_tuple				n_vector;
	float				diameter;
	float				height;
	t_color				colors;
	struct s_cylindre	*next;
}						t_cylindre;

typedef struct s_data
{
	t_alight			*alight;
	t_camera			*camera;
	t_light				*light;
	t_sphere			**sphere;
	t_plan				**plan;
	t_cylindre			**cylindre;
	int					counter[6];
}						t_data;

typedef struct s_win
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_win;

void					print_char_tab(char **tab);
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PARSING                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int						scene_name_check(char *av);
t_data					init_all_data(int fd);
void					null_data(t_data *data);
int						init_corresponding_data(char *file_data, t_data *data);
int						init_data_w_line(t_data *data, t_dtype type,
							char **data_split);
t_dtype					determine_type(char *data);
int						char_tab_len(char **tab);
void					free_char_tab(char **tab);
int						is_string_float(char *str);
int						verify_colors(char *str);
int						verify_alight(char **data);
int						verify_camera(char **data);
int						verify_light(char **data);
int						verify_plan(char **data);
int						verify_sphere(char **data);
int						verify_cylindre(char **data);
int						verified_content(char **data, t_dtype type);
int						verify_coord(char *data);
int						verify_vect(char *data);
int						verify_fov(char *data);
int						verify_colors_syntax(char *data);
int						check_fov_syntax(char *data);
int						check_vect_syntax(char *data);
int						check_coord_syntax(char *data);

int						init_alight(t_data *data, char **data_split);
int						init_camera(t_data *data, char **data_split);
int						init_light(t_data *data, char **data_split);
int						init_sphere(t_data *data, char **data_split);
int						init_plan(t_data *data, char **data_split);
int						init_cylindre(t_data *data, char **data_split);
t_dtype					determine_type(char *data);
void					null_data(t_data *data);
void					print_all_data(t_data *data);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   LST                                      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_cylindre				*cylindre_lstlast(t_cylindre *lst);
int						cylindre_lstsize(t_cylindre *lst);
void					cylindre_lstadd_back(t_cylindre **lst, t_cylindre *new);
void					cylindre_lstfree(t_cylindre **lst);

t_sphere				*sphere_lstlast(t_sphere *lst);
int						sphere_lstsize(t_sphere *lst);
void					sphere_lstadd_back(t_sphere **lst, t_sphere *new);
void					sphere_lstfree(t_sphere **lst);

t_plan					*plan_lstlast(t_plan *lst);
int						plan_lstsize(t_plan *lst);
void					plan_lstadd_back(t_plan **lst, t_plan *new);
void					plan_lstfree(t_plan **lst);

void					print_sphere_list(t_sphere **sphere_list);
void					print_plan_list(t_plan **plan_list);
void					print_cylindre_list(t_cylindre **cylindre_list);

void					free_data(t_data *data);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   TUPLE_CALCULATION                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										TUPLE									//
t_tuple					ft_init_tuple(float x, float y, float z, float w);
t_tuple					ft_sum_tuple(t_tuple t1, t_tuple t2);
t_tuple					ft_dif_tuple(t_tuple t1, t_tuple t2);
t_tuple					ft_neg_tuple(t_tuple t);
t_tuple					ft_mult_vector(t_tuple v, float scale);
t_tuple					ft_div_vector(t_tuple v, int scale);
int						ft_comp_float(float n1, float n2);
int						same_tuple(t_tuple t1, t_tuple t2);
float					ft_magnitude(t_tuple v);
t_tuple					ft_normalization(t_tuple v);
float					ft_dotproduct(t_tuple v1, t_tuple v2);
t_tuple					cross_product(t_tuple v1, t_tuple v2);

//										COLORS									//

t_color					ft_sum_color(t_color c1, t_color c2);
t_color					ft_dif_color(t_color c1, t_color c2);
t_color					ft_mult_color(t_color c, int scalar);
t_color					ft_mult_color_tog(t_color c1, t_color c2);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   MATRICE                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										CALCUL								//

float					**ft_mult_mat(float **mat1, float **mat2);
t_tuple					ft_mult_mat_tuple(t_tuple *tuple, float **mat);
void					ft_transpose(float mat[4][4]);
int						ft_comp_mat(float mat1[4][4], float mat2[4][4]);
float					**ft_inversion(float **matrice, int row_col);

//										UTILS								//

float					**ft_matcre(float *tab, int row_col);
void					ft_free_mat(float **mat, int row_col);
float					**ft_create_mat_null(int row_col);
void					print_matrix(float **mat, int row_col);
float					**ft_submat(float **matrice, int row_col, int row,
							int col);

//										UTILS2								//
float					**identity_matrix(int size);

//										DETER_COFAC							//

float					ft_deter2_2(float **mat);
float					ft_determinant3_3(float **mat);
float					ft_cofactorinversion(float **mat, int row, int col);
float					ft_determinant4_4(float **matrice);
float					ft_cofactor2_2(float **mat, int row, int col);

//										TRANSFORMATION						//

float					**translation(float x, float y, float z);
float					**scaling(float x, float y, float z);
void					rotation_x(t_tuple *t, float rad);
void					rotation_y(t_tuple *t, float rad);
void					rotation_z(t_tuple *t, float rad);
float					**shearing(float shear[6]);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   RAYS                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_ray					ft_ray(t_tuple origin, t_tuple direction);
t_tuple					ft_position(t_ray r, float t);

// INTERSECTIONS //
t_intersection			*ft_intersections_tab(int count, ...);
void					ft_sort_intersections(t_intersection *intersections,
							int count);
t_intersection			*ft_hit(t_intersection *intersections, int count);
t_intersection			*ft_intersect(t_ray ray, t_sphere *sphere);
t_discriminant			ft_discriminant(t_ray ray, t_sphere *sphere);
t_sphere				ft_sphere(t_tuple center, float radius);
t_intersection			ft_intersection(float t, t_sphere *sphere);
t_ray					ray_transform(t_ray ray, float **matrix);
t_tuple					ft_mult_matrix_tuple(float **matrix, t_tuple tuple);
void					set_transform(t_sphere *sphere, float **matrix);
#endif
