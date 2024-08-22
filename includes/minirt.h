/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/08/22 15:06:11 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define EPSILON 0.0001
# define INFINITY 1e10
# define SIZE_X 500
# define SIZE_Y 500
# define SPHERE 0
# define PLAN 1
# define CYLINDER 2
# define CONE 3
# define FIRST 0
# define SECOND 1
# define THIRD 2
# define ALL 3
# define NONE 4
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
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

typedef struct s_image
{
	void				*img_ptr;
	int					width;
	int					height;
	int					bpp;
	int					size_line;
	int					endian;
	char				*data;
}						t_image;

typedef enum e_objects
{
	Notype,
	Sphere,
	Plan,
	Cylinder,
	Cone
}						t_objects;

typedef enum e_dtype
{
	NOTYPE,
	A,
	C,
	L,
	SP,
	PL,
	CY,
	CO
}						t_dtype;

typedef struct s_wall
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

typedef struct s_ray_norme
{
	double				xoffset;
	double				yoffset;
	double				world_x;
	double				world_y;
	t_tuple				pixel;
	t_tuple				origin;
	t_tuple				direction;
	t_tuple				*tmp_comput;
}						t_ray_norme;

typedef struct s_color
{
	double				r;
	double				g;
	double				b;
	int					text_color;
}						t_color;

typedef struct s_define_patt_norme
{
	t_color				eff_color;
	t_tuple				object_point;
	float				theta;
	float				phi;
	float				u;
	float				v;
	t_tuple				point_object;
}						t_define_patt_norme;

typedef struct s_pattern
{
	t_color				*a;
	t_color				*b;
	float				**transform;
}						t_pattern;

typedef struct s_discriminant
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
	t_color				colors;
}						t_alight;

typedef struct s_light
{
	t_tuple				position;
	t_color				colors;
	t_color				intensity;
	struct s_light		*next;
}						t_light;

typedef struct s_material
{
	t_color				color;
	float				ambiant;
	float				ambiant_intensity;
	t_color				*ambiant_color;
	float				diffuse;
	float				specular;
	float				shininess;
	t_pattern			*pattern;
	int					is_texture;
	t_image				*texture;
	int					is_pattern;
	t_objects			type;
}						t_material;

typedef struct s_sphere
{
	t_tuple				center;
	t_color				colors;
	struct s_sphere		*next;
	float				radius;
	float				**matrix;
	t_material			*m;
}						t_sphere;

typedef struct s_cylinder
{
	t_tuple				n_vector;
	float				radius;
	float				y_max;
	float				y_min;
	t_material			*m;
	float				**matrix;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_cone
{
	t_tuple				coord;
	t_tuple				n_vector;
	float				angle;
	float				radius;
	float				y_max;
	float				y_min;
	t_material			*m;
	t_color				colors;
	float				**matrix;
	struct s_cone		*next;
}						t_cone;

typedef struct s_plan
{
	t_tuple				coord;
	t_tuple				normal;
	t_tuple				vector;
	t_color				colors;
	float				**matrix;
	t_material			*m;
	struct s_plan		*next;
	int					type;
}						t_plan;

typedef struct s_camera
{
	float				hsize;
	float				vsize;
	t_tuple				vector;
	float				fov;
	float				**matrix;
	float				pixel_size;
	float				half_width;
	float				half_height;
}						t_camera;

typedef struct s_comps
{
	float				t;
	int					type;
	t_sphere			*sphere;
	t_plan				*plan;
	t_cylinder			*cylinder;
	t_cone				*cone;
	t_tuple				point;
	t_tuple				eyev;
	t_tuple				normalv;
	t_tuple				over_point;
	int					inside;
	int					in_shadow;
}						t_comps;

typedef struct s_intersection
{
	float				t;
	int					count;
	int					status;
	t_sphere			*sphere;
	t_plan				*plan;
	t_cylinder			*cylinder;
	t_cone				*cone;
}						t_intersection;

typedef struct s_shadowed_norme
{
	t_tuple				v;
	t_tuple				direction;
	float				distance;
	t_intersection		*intersections;
	t_intersection		*hit;
	t_ray				r;
	t_light				*curr;
}						t_shadowed_norme;

typedef struct s_world
{
	t_color				*alight;
	float				alight_intensity;
	t_camera			*camera;
	t_light				**light;
	t_sphere			**sphere;
	t_plan				**plan;
	t_cylinder			**cylinder;
	t_cone				**cone;
	pthread_mutex_t		*pixel_put;
	int					counter[6];
}						t_world;

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

typedef struct s_thread
{
	pthread_t			pthread_id;
	t_world				*data;
	t_win				*win;
	int					index;
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
}						t_thread;

typedef struct s_render_norme
{
	t_thread			*thread;
	t_camera			*camera;
	t_win				*win;
	t_world				*data;
	t_ray				ray;
	t_color				color;
	int					color_int;
	int					x;
	int					y;
}						t_render_norme;

typedef struct s_complete
{
	t_thread			*thread;
	t_win				*win;
	t_world				*data;
}						t_complete;

typedef struct s_norme_set_patt
{
	t_tuple				*object_point;
	t_tuple				*pattern_point;
	float				theta;
	float				phi;
	float				u;
	float				v;
}						t_norme_set_patt;

typedef struct s_norme_cone
{
	float				abc[3];
	float				discriminant;
	t_ray				new_ray;
	float				y0;
	t_intersection		t;
}						t_norme_cone;

typedef struct s_norme_cylinder
{
	float				tab[4];
	t_intersection		t;
	t_ray				new_ray;
	float				y0;
}						t_norme_cylinder;

typedef struct s_norme_caps_cylinder
{
	t_intersection		t;
	t_ray				new_ray;
	float				t0;
	float				t1;
}						t_norme_caps_cylinder;

typedef struct s_norme_submat
{
	int					row;
	int					col;
	int					i;
	int					k;
	int					l;
}						t_norme_submat;

typedef struct s_norme_submat2
{
	float				**mat;
	int					i;
	int					j;
}						t_norme_submat2;

typedef struct s_norme_planar_mapping
{
	float				plane_width;
	float				plane_height;
}						t_norme_planar_mapping;

typedef struct s_norme_intersect_world
{
	t_intersection		*t_tab;
	int					count;
	t_sphere			*sphere;
	t_plan				*plan;
	t_cylinder			*cylinder;
	t_cone				*cone;
}						t_norme_intersect_world;

typedef struct s_norme_sphere_intersect
{
	t_intersection		t[2];
	t_discriminant		dis;
	t_ray				new_ray;
}						t_norme_sphere_intersect;

typedef struct s_norme_lighting
{
	t_color				eff;
	t_tuple				lightv;
	t_color				diffuse;
	t_color				specular;
	t_tuple				reflectv;
	t_color				ambiant;
	float				factor;
	float				reflect_dot_eye;
	float				light_dot_normal;
	int					is_textured;
	t_color				final_color;
	t_tuple				normalv;
	t_tuple				eyev;
}						t_norme_lighting;

typedef struct s_norme_init_pattern
{
	char				**col_split;
	char				**first_color;
	char				**second_color;
	t_color				*p_color_1;
	t_color				*p_color_2;
}						t_norme_init_pattern;

typedef struct s_norme_main
{
	int					fd;
	t_world				*data;
	t_win				*win;
	t_complete			*complete;
}						t_norme_main;

typedef struct s_norme_threads
{
	int					i;
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
}						t_norme_threads;

typedef struct s_types_check
{
	int					a;
	int					c;
}						t_types_check;

void					print_char_tab(char **tab);
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   PARSING                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

void					ft_add_type(t_types_check *types, t_dtype type);
void					ft_check_types(t_types_check types, t_world **data,
							t_win *mlx);
int						scene_name_check(char *av);
double					ft_atof(char *str);
void					atof_util(int *i, int *sign, char *str);
t_world					*init_all_data(int fd, t_win *mlx);
void					null_data(t_world *data);
int						init_corresponding_data(char *file_data, t_world *data,
							t_win *mlx, t_types_check *types);
int						init_data_w_line(t_world *data, t_dtype type,
							char **data_split, t_win *mlx);
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
int						verify_cylinder(char **data);
int						verify_cone(char **data);
int						verified_content(char **data, t_dtype type);
int						verify_coord(char *data);
int						verify_vect(char *data);
int						verify_fov(char *data);
int						verify_colors_syntax(char *data);
int						verify_texture_and_pattern(char *data);
int						verify_pattern(char *pattern, char ***upper_split);
int						verify_texture(char *pattern, char ***upper_split);
int						check_fov_syntax(char *data);
int						check_vect_syntax(char *data);
int						check_coord_syntax(char *data);

int						init_alight(t_world *data, char **data_split);
int						init_camera(t_world *data, char **data_split);
int						init_light(t_world *data, char **data_split);
int						init_sphere(t_world *data, char **data_split,
							t_win *mlx);
int						init_plan(t_world *data, char **data_split, t_win *mlx);
int						init_cylinder(t_world *data, char **data_split,
							t_win *mlx);
int						init_cone(t_world *data, char **data_split, t_win *mlx);
t_dtype					determine_type(char *data);
void					null_data(t_world *data);
void					print_all_data(t_world *data);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   LST                                      */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_cylinder				*cylinder_lstlast(t_cylinder *lst);
int						cylinder_lstsize(t_cylinder *lst);
void					cylinder_lstadd_back(t_cylinder **lst, t_cylinder *new);
void					cylinder_lstfree(t_cylinder **lst);

t_sphere				*sphere_lstlast(t_sphere *lst);
int						sphere_lstsize(t_sphere *lst);
void					sphere_lstadd_back(t_sphere **lst, t_sphere *new);
void					sphere_lstfree(t_sphere **lst);

t_plan					*plan_lstlast(t_plan *lst);
int						plan_lstsize(t_plan *lst);
void					plan_lstadd_back(t_plan **lst, t_plan *new);
void					plan_lstfree(t_plan **lst);
void					free_plan(t_plan **plan, void *mlx);

t_cone					*cone_lstlast(t_cone *lst);
int						cone_lstsize(t_cone *lst);
void					cone_lstadd_back(t_cone **lst, t_cone *new);
void					cone_lstfree(t_cone **lst);

t_light					*light_lstlast(t_light *lst);
int						light_lstsize(t_light *lst);
void					light_lstadd_back(t_light **lst, t_light *new);
void					light_lstfree(t_light **lst);
void					free_light(t_light **light);

void					print_sphere_list(t_sphere **sphere_list);
void					print_plan_list(t_plan **plan_list);
void					print_cylinder_list(t_cylinder **cylinder_list);

void					free_data(t_world **data, void *mlx_ptr);
void					free_material(t_material *material, void *mlx);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   TUPLE_CALCULATION                        */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										TUPLE								//
t_tuple					*ft_init_tuple(float x, float y, float z, float w);
t_tuple					ft_init_tuple_reg(float x, float y, float z, float w);
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

//										COLORS								//

t_color					ft_sum_color(t_color c1, t_color c2);
t_color					ft_dif_color(t_color c1, t_color c2);
t_color					ft_mult_color(t_color c, float scalar);
t_color					ft_mult_color_tog(t_color c, t_color c2);
t_color					*ft_color(float r, float g, float b);
t_pattern				*ft_pattern(t_color *a, t_color *b);
t_color					*ft_stripe_at(t_pattern *pattern, t_tuple point);
t_color					*ft_chkr_at(t_pattern *pattern, float u, float v);
t_material				*ft_set_pattern(t_comps *comps, int type);
t_color					ft_color_reg(float r, float g, float b);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   MATRICE                                  */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										CALCUL								//

float					**ft_mult_mat(float **mat1, float **mat2,
							int free_data);
t_tuple					ft_mult_mat_tuple(t_tuple *tuple, float **mat,
							int free_data);
float					**ft_transpose(float **mat);
int						ft_comp_mat(float **mat1, float **mat2, int row_col);
float					**ft_inversion(float **matrice, int row_col);

//										UTILS								//

float					**ft_matcre(float *tab, int row_col);
void					ft_free_mat(float **mat, int row_col);
float					**ft_create_mat_null(int row_col);
void					print_matrix(float **mat, int row_col);
float					**ft_submat(float **matrice, int row_col, int row,
							int col);
void					submat_helper(float **new_mat, float **matrice,
							int row_col, t_norme_submat v);

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
float					**rotation_x(float rad);
float					**rotation_y(float rad);
float					**rotation_z(float rad);
float					**shearing(float shear[6]);
void					set_transform(t_sphere *sphere, float **matrix);

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
t_sphere				*ft_sphere(void);
t_intersection			ft_intersection(float t, t_sphere *sphere);
t_ray					ray_transform(t_ray ray, float **matrix);
t_tuple					ft_mult_matrix_tuple(float **matrix, t_tuple *tuple,
							int free_id);
void					set_transform(t_sphere *sphere, float **matrix);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   REFLECTIONS                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_tuple					ft_reflect(t_tuple in, t_tuple normal);
t_material				*ft_material(void);
t_light					*ft_point_light(t_tuple *position, t_color *intensity);
void					ft_point_light2(t_light *light, t_tuple position,
							t_color intensity);

t_color					ft_lighting(t_material *m, t_light light,
							t_comps *comps, void *object);
void					color_black(t_color *color);
t_tuple					ft_normal_at(t_comps comps, t_tuple world_point);
unsigned int			color_to_int(t_color color);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   CAMERA                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_camera				*ft_new_camera(float hsize, float vsize, double fov);
float					compute_pixel_size(t_camera *camera);
t_ray					ray_for_pixel(t_camera *camera, int px, int py);
void					*render(void *world);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   SCENES                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//										CALCUL								//

float					**ft_mult_mat(float **mat1, float **mat2,
							int free_data);
t_tuple					ft_mult_mat_tuple(t_tuple *tuple, float **mat,
							int free_data);
float					**ft_transpose(float **mat);
int						ft_comp_mat(float **mat1, float **mat2, int row_col);
float					**ft_inversion(float **matrice, int row_col);

//										UTILS								//

t_world					*ft_default_world(void);
t_comps					ft_prepare_computations(t_intersection *i, t_ray ray);
t_intersection			*ft_intersect_world(t_ray ray, t_world **data);
t_color					ft_shade_hit(t_world *data, t_comps *comps);
float					**ft_view_transform(t_tuple from, t_tuple to,
							t_tuple up);
t_color					ft_color_at(t_world *data, t_ray ray);

int						ft_is_shadowed(t_world *world, t_tuple point);
void					put_pixel(t_win *win, int x, int y, unsigned int color);
void					ft_plan_intersect(t_intersection **t_tab, t_plan **plan,
							t_ray ray, int *count);
t_plan					*ft_plan(void);
void					ft_cylinder_intersect(t_intersection **t_tab,
							t_cylinder **cylinder, t_ray ray, int *count);
t_cylinder				*ft_cylinder(void);
void					cylinder_intersect_helper(t_norme_cylinder *v,
							t_cylinder **cylinder, int *count,
							t_intersection **t_tab);
t_intersection			*ft_add_t(t_intersection **t_tab, t_intersection t[2],
							int count);
t_intersection			*ft_add_one_t(t_intersection **t_tab, t_intersection t,
							int count);
void					ft_cylinder_caps_intersect(t_intersection **t_tab,
							t_cylinder **cylinder, t_ray ray, int *count);
void					cylinder_caps_helper(t_intersection *t, int *count,
							t_cylinder *cylinder, float t_n);
void					ft_cone_intersect(t_intersection **t_tab, t_cone **cone,
							t_ray ray, int *count);
t_cone					*ft_cone(void);
void					cone_intersect_helper(t_norme_cone *v, t_cone **cone);
void					cone_intersect_helper2(t_norme_cone *v, int *count,
							t_cone **cone, t_intersection **t_tab);

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                   TEXTURES                                 */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

t_material				*ft_texture(char *path, void *mlx);
int						ft_texture_color_to_int(t_color color);
void					cylindrical_mapping(t_tuple point_object,
							t_image *image, t_color *color);
void					planar_mapping(t_tuple point_object, t_image *image,
							t_color *color, t_norme_planar_mapping v);
void					spherical_mapping(t_tuple point, t_image *image,
							t_color *color);
void					get_interpolated_color(float u, float v, t_image *image,
							t_color *color);
uint8_t					*get_pixel(t_image *image, int x, int y);
t_image					*load_xpm_image(void *mlx_ptr, const char *file_path);
t_color					define_eff_color(t_objects type, t_tuple position,
							void *object, t_light light);
t_color					ft_spherical(t_tuple position, t_sphere sphere,
							t_light light);
t_color					ft_planar(t_tuple position, t_plan plan, t_light light);
t_color					ft_cylindrical(t_tuple position, t_cylinder cylinder,
							t_light light);

int						ft_check_caps(t_ray ray, float t, float radius);
void					ft_check_cone_caps(t_intersection **t_tab,
							t_cone **cone, t_ray ray, int *count);
int						ft_equal_tuple(t_tuple *t1, t_tuple *t2);
void					calculate_plane_dimensions(float **matrix, float *width,
							float *height);
void					initialize_corners(t_tuple corners[4]);
void					destroy_t_win(t_win *win);
t_color					define_pattern_color(t_objects type, t_tuple position,
							void *object);
int						init_helper(t_world *data, t_dtype type,
							char **data_split, t_win *mlx);
t_tuple					calculate_sphere_normal(t_comps object,
							t_tuple world_point, float ***attr_mat);
t_tuple					calculate_cylinder_normal(t_comps object,
							t_tuple world_point, float ***attr_mat);
t_tuple					calculate_cone_normal(t_comps object,
							t_tuple world_point, float ***attr_mat);
void					thread_attribution(t_thread *thread,
							t_complete *complete, t_norme_threads *v);
void					destroy_t_win(t_win *win);
void					free_win_classic(t_win *win);
void					start_threads(t_complete *complete);
void					setup_hooks(t_win *win, t_complete *complete);
int						exit_window(t_complete *complete);
t_material				*set_sphere_patt(t_comps *comps, t_norme_set_patt *v);
t_material				*set_plan_patt(t_comps *comps, t_norme_set_patt *v);
t_material				*set_cone_patt(t_comps *comps, t_norme_set_patt *v);
t_material				*set_cylinder_patt(t_comps *comps, t_norme_set_patt *v);
void					attribute_cone(t_intersection *t, int *count,
							t_cone *cone);
float					distance(t_tuple a, t_tuple b);
void					ft_sphere_comps(t_comps *comps, t_sphere *sphere);
t_comps					ft_null_comps(void);
void					ft_cone_comps(t_comps *comps, t_cone *cone);
void					ft_cylinder_comps(t_comps *comps, t_cylinder *cylinder);
void					ft_plan_comps(t_comps *comps, t_plan *plan);
int						prepare_all_data(t_norme_intersect_world *v);
void					define_tmp_color(t_color *tmp_color, t_comps *comps,
							t_light *light, int in_shadow);
void					ft_lighting_helper(t_norme_lighting *v, t_light light,
							int in_shadow, t_material *m);
void					ft_lighting_helper2(t_norme_lighting *v, t_tuple eyev,
							t_tuple normalv);
void					ft_init_light_pos(t_light *light, char **split);
void					ft_init_light_intensity(t_light *light, char **split,
							float intensity);
t_light					*ft_init_light(void);
int						ft_init_all_light_values(char **data_split,
							t_light *light);
int						ft_init_sphere_pattern(char **split, t_sphere *sphere);
int						ft_init_text_or_patt_sphere(char **data_split,
							t_sphere *sphere, t_win *mlx);
void					free_sphere(t_sphere **sphere, void *mlx);
int						ft_init_sphere_helper(char **data_split,
							t_sphere *sphere, t_win *mlx);
int						add_sphere_to_lst(t_world *data, t_sphere *sphere);
int						ft_init_cylinder_helper(char **data_split,
							t_cylinder *cylinder, int y);
int						ft_init_text_or_patt_cyl(char **data_split,
							t_cylinder *cylinder, t_win *mlx);
int						ft_init_cylinder_pattern(char **split,
							t_cylinder *cylinder);
int						ft_init_cylinder_helper2(t_cylinder *cylinder,
							t_world *data, char **data_split, t_win *mlx);
int						ft_init_plan_pattern(char **split, t_plan *plan);
int						ft_init_text_or_patt_plan(char **data_split,
							t_plan *plan, t_win *mlx);
int						ft_init_plan_helper(char **data_split, t_plan *plan);
int						ft_init_plan_helper2(t_world *data, char **data_split,
							t_plan *plan, void *mlx);
int						ft_init_text_or_patt_cone(char **data_split,
							t_cone *cone, t_win *mlx);
int						ft_init_cone_helper(char **data_split, t_cone *cone,
							int y);
int						ft_init_cone_pattern(char **split, t_cone *cone);
int						ft_init_cone_helper2(t_cone *cone, t_world *data,
							char **data_split, t_win *mlx);
void					init_m_color(t_material *m, char **split);
int						add_cylinder_to_lst(t_world *data,
							t_cylinder *cylinder);
int						add_cone_to_lst(t_world *data, t_cone *cone);
int						add_plan_to_lst(t_world *data, t_plan *plan);
void					ft_start_thread_helper(t_norme_threads *v);
void					ft_start_thread_helper2(t_norme_threads *v,
							t_complete *complete);
#endif
