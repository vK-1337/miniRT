/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/06/08 13:50:43 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define EPSILON 0.001
#define INFINITY 1e10
#define SIZE_X 500
#define SIZE_Y 500
#define CENTER_X SIZE_X / 2
#define CENTER_Y SIZE_Y / 2
#define SPHERE 0
#define PLAN 1
#define CYLINDER 2
#define CONE 3
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

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
} t_dtype;

typedef struct t_wall
{
	float x;
	float y;
	float z;
	float size;
} t_wall;

typedef struct s_tuple
{
	float x;
	float y;
	float z;
	float w;
} t_tuple;

typedef struct s_color
{
	double r;
	double g;
	double b;
} t_color;

typedef struct s_pattern
{
	t_color *a;
	t_color *b;
	float **transform;
} t_pattern;

typedef struct t_discriminant
{
	float a;
	float b;
	float c;
	float result;
} t_discriminant;

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
} t_ray;

typedef struct s_alight
{
	float alight;
	t_color colors;
} t_alight;

typedef struct s_light
{
	t_tuple position;
	float light_ratio;
	t_color colors;
	t_color intensity;
	struct s_light *next;
} t_light;

typedef struct s_material
{
	t_color *color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	t_pattern *pattern;
} t_material;

typedef struct s_sphere
{
	t_tuple center;
	t_color colors;
	struct s_sphere *next;
	float radius;
	float **matrix;
	t_material *material;
} t_sphere;

typedef struct s_cylinder
{
	t_tuple coord;
	t_tuple n_vector;
	float radius;
	float y_max;
	float y_min;
	t_material *material;
	t_color colors;
	float **matrix;
	struct s_cylinder *next;
	int closed;
} t_cylinder;

typedef struct s_cone
{
	t_tuple coord;
	t_tuple n_vector;
	float angle;
	float radius;
	float y_max;
	float y_min;
	t_material *material;
	t_color colors;
	float **matrix;
	struct s_cone *next;
	int closed;
} t_cone;

typedef struct s_plan
{
	t_tuple coord;
	t_tuple normal;
	t_tuple vector;
	t_color colors;
	float **matrix;
	t_material *material;
	struct s_plan *next;
	int type;
} t_plan;

typedef struct s_camera
{
	float hsize;
	float vsize;
	t_tuple vector;
	float fov;
	float **matrix;
	float pixel_size;
	float half_width;
	float half_height;
} t_camera;

typedef struct s_comps
{
	float t;
	int type;
	t_sphere *sphere;
	t_plan *plan;
	t_cylinder *cylinder;
	t_cone *cone;
	t_tuple point;
	t_tuple eyev;
	t_tuple normalv;
	t_tuple over_point;
	int inside;
} t_comps;

typedef struct s_intersection
{
	float t;
	int count;
	int status;
	t_sphere *sphere;
	t_plan *plan;
	t_cylinder *cylinder;
	t_cone *cone;
} t_intersection;

typedef struct s_world
{
	t_alight *alight;
	t_camera *camera;
	t_light *light;
	t_sphere **sphere;
	t_plan **plan;
	t_cylinder **cylinder;
	t_cone **cone;
	int counter[6];
} t_world;

typedef struct s_win
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_win;

void print_char_tab(char **tab);
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PARSING                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

int scene_name_check(char *av); // Convert color to int
t_world init_all_data(int fd);
void null_data(t_world *data);
int init_corresponding_data(char *file_data, t_world *data);
int init_data_w_line(t_world *data, t_dtype type,
					 char **data_split);
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
int verify_cylinder(char **data);
int verified_content(char **data, t_dtype type);
int verify_coord(char *data);
int verify_vect(char *data);
int verify_fov(char *data);
int verify_colors_syntax(char *data);
int check_fov_syntax(char *data);
int check_vect_syntax(char *data);
int check_coord_syntax(char *data);

int init_alight(t_world *data, char **data_split);
int init_camera(t_world *data, char **data_split);
int init_light(t_world *data, char **data_split);
int init_sphere(t_world *data, char **data_split);
int init_plan(t_world *data, char **data_split);
int init_cylinder(t_world *data, char **data_split);
t_dtype determine_type(char *data);
void null_data(t_world *data);
void print_all_data(t_world *data);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   LST                                      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_cylinder *cylinder_lstlast(t_cylinder *lst);
int cylinder_lstsize(t_cylinder *lst);
void cylinder_lstadd_back(t_cylinder **lst, t_cylinder *new);
void cylinder_lstfree(t_cylinder **lst);

t_sphere *sphere_lstlast(t_sphere *lst);
int sphere_lstsize(t_sphere *lst);
void sphere_lstadd_back(t_sphere **lst, t_sphere *new);
void sphere_lstfree(t_sphere **lst);

t_plan *plan_lstlast(t_plan *lst);
int plan_lstsize(t_plan *lst);
void plan_lstadd_back(t_plan **lst, t_plan *new);
void plan_lstfree(t_plan **lst);

void print_sphere_list(t_sphere **sphere_list);
void print_plan_list(t_plan **plan_list);
void print_cylinder_list(t_cylinder **cylinder_list);

void free_data(t_world *data);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   TUPLE_CALCULATION                        */
/*                                                                            */
/*                                                                            */
/*************************************************************	printf("Hit\n");*****************/

//										TUPLE									//
t_tuple *ft_init_tuple(float x, float y, float z, float w);
t_tuple ft_sum_tuple(t_tuple t1, t_tuple t2);
t_tuple ft_dif_tuple(t_tuple t1, t_tuple t2);
t_tuple ft_neg_tuple(t_tuple t);
t_tuple ft_mult_vector(t_tuple v, float scale);
t_tuple ft_div_vector(t_tuple v, int scale);
int ft_comp_float(float n1, float n2);
int same_tuple(t_tuple t1, t_tuple t2);
float ft_magnitude(t_tuple v);
t_tuple ft_normalization(t_tuple v);
float ft_dotproduct(t_tuple v1, t_tuple v2);
t_tuple cross_product(t_tuple v1, t_tuple v2);

//										COLORS									//

t_color ft_sum_color(t_color c1, t_color c2);
t_color ft_dif_color(t_color c1, t_color c2);
t_color ft_mult_color(t_color c, float scalar);
t_color ft_mult_color_tog(t_color c, t_color c2);
t_color *ft_color(float r, float g, float b);
t_pattern *ft_pattern(t_color *a, t_color *b);
t_color *ft_stripe_at(t_pattern *pattern, t_tuple point);
t_material *ft_set_pattern(t_comps *comps, int type);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   MATRICE                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										CALCUL								//

float **ft_mult_mat(float **mat1, float **mat2);
t_tuple ft_mult_mat_tuple(t_tuple *tuple, float **mat);
float **ft_transpose(float **mat);
int ft_comp_mat(float **mat1, float **mat2, int row_col);
float **ft_inversion(float **matrice, int row_col);

//										UTILS								//

float **ft_matcre(float *tab, int row_col);
void ft_free_mat(float **mat, int row_col);
float **ft_create_mat_null(int row_col);
void print_matrix(float **mat, int row_col);
float **ft_submat(float **matrice, int row_col, int row,
				  int col);

//										UTILS2								//
float **identity_matrix(int size);

//										DETER_COFAC							//

float ft_deter2_2(float **mat);
float ft_determinant3_3(float **mat);
float ft_cofactorinversion(float **mat, int row, int col);
float ft_determinant4_4(float **matrice);
float ft_cofactor2_2(float **mat, int row, int col);

//										TRANSFORMATION						//

float **translation(float x, float y, float z);
float **scaling(float x, float y, float z);
float **rotation_x(float rad);
float **rotation_y(float rad);
float **rotation_z(float rad);
float **shearing(float shear[6]);
void set_transform(t_sphere *sphere, float **matrix);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   RAYS                                     */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_ray ft_ray(t_tuple origin, t_tuple direction);
t_tuple ft_position(t_ray r, float t);

// INTERSECTIONS //
t_intersection *ft_intersections_tab(int count, ...);
void ft_sort_intersections(t_intersection *intersections,
						   int count);
t_intersection *ft_hit(t_intersection *intersections, int count);
t_intersection *ft_intersect(t_ray ray, t_sphere *sphere);
t_discriminant ft_discriminant(t_ray ray, t_sphere *sphere);
t_sphere *ft_sphere(void);
t_intersection ft_intersection(float t, t_sphere *sphere);
t_ray ray_transform(t_ray ray, float **matrix);
t_tuple ft_mult_matrix_tuple(float **matrix, t_tuple tuple);
void set_transform(t_sphere *sphere, float **matrix);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   REFLECTIONS                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_tuple ft_reflect(t_tuple in, t_tuple normal);
t_material *ft_material(void);
t_light *ft_point_light(t_tuple *position, t_color *intensity);
void ft_point_light2(t_light *light, t_tuple position,
					 t_color intensity);
t_color ft_lighting(t_material *m, t_light light,
					t_tuple position, t_tuple eyev, t_tuple normalv,
					int in_shadow);
void color_black(t_color *color);
t_tuple ft_normal_at(t_comps comps, t_tuple world_point);
unsigned int color_to_int(t_color color);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   CAMERA                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_camera ft_new_camera(float hsize, float vsize, double fov);
float compute_pixel_size(t_camera *camera);
t_ray ray_for_pixel(t_camera *camera, int px, int py);
void render(t_camera *camera, t_world *world, t_win *win);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   SCENES									  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_world *ft_default_world(void);
t_comps ft_prepare_computations(t_intersection *i, t_ray ray);
t_intersection *ft_intersect_world(t_ray ray, t_world **data);
t_color ft_shade_hit(t_world *data, t_comps *comps);
float **ft_view_transform(t_tuple from, t_tuple to,
						  t_tuple up);
t_color ft_color_at(t_world *data, t_ray ray);

int ft_is_shadowed(t_world *world, t_tuple point);
void put_pixel(t_win *win, int x, int y, unsigned int color);
void ft_plan_intersect(t_intersection **t_tab, t_plan **plan,
					   t_ray ray, int *count);
t_plan *ft_plan(void);
void ft_cylinder_intersect(t_intersection **t_tab, t_cylinder **cylinder, t_ray ray, int *count);
t_cylinder *ft_cylinder(void);
t_intersection *ft_add_t(t_intersection *t_tab, t_intersection t[2], int count);
t_intersection *ft_add_one_t(t_intersection *t_tab, t_intersection t, int count);
void ft_cylinder_caps_intersect(t_intersection **t_tab, t_cylinder **cylinder, t_ray ray, int *count);
void ft_cone_intersect(t_intersection **t_tab, t_cone **cone, t_ray ray, int *count);
t_cone *ft_cone(void);

#endif
