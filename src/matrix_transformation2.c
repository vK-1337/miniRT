/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:48:53 by udumas            #+#    #+#             */
/*   Updated: 2024/05/29 11:13:37 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float **shearing(float shear[6])
{
    float **mat;

    mat = identity_matrix(4);
    mat[0][1] = shear[0];
    mat[0][2] = shear[1];
    mat[1][0] = shear[2];
    mat[1][2] = shear[3];
    mat[2][0] = shear[4];
    mat[2][1] = shear[5];
    return (mat);
}

// void	put_pixel(t_win *win, int x, int y, int color)
// {
// 	char	*dst;

//   if ((x > SIZE_X || x < 0)|| (y > SIZE_Y || y < 0))
//     return ;
// 	dst = win->addr + (y * win->line_length + x
// 			* (win->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// int exit_window(t_win *win)
// {
//   // mlx_destroy_image(fractal->mlx, fractal->img);
// 	mlx_destroy_window(win->mlx, win->win);
// 	mlx_destroy_display(win->mlx);
// 	free(win->mlx);
// 	free(win);
// 	exit(1);
// 	return (0);
// }

// t_win *init_mlx(void)
// {
//   t_win *win;

//   win = malloc(sizeof(t_win));
//   win->mlx = mlx_init();
//   win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
//   win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
//   win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
// 			&win->line_length, &win->endian);
//   return (win);
// }

// int main()
// {
//     t_win *win;
//     float **mat_rotation;
//     t_tuple hour_pos;
//     win = init_mlx();
//     mlx_hook(win->win, 17, 0, exit_window, win);
//     t_tuple center = ft_init_tuple(SIZE_X/2, SIZE_Y/2, 0, 1);
//     t_tuple twelve = ft_init_tuple(SIZE_X/2, SIZE_Y/2, 100, 1);

//     for (int hour =0; hour < 12; hour++)
//     {
//         hour_pos = ft_dif_tuple(center, twelve);
//         rotation_y(&hour_pos, M_PI/6 * hour);
//         hour_pos = ft_sum_tuple(hour_pos, center);
//         hour_pos.z += SIZE_Y/2;
//         put_pixel(win, round(hour_pos.x), round(hour_pos.z), 0xFFFFFF);
//     }
//     put_pixel(win, center.x, center.y, 0xFFFFFF);
//     mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0 );
//     mlx_loop(win->mlx);
// }