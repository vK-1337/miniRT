/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/22 20:19:07 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// int main(int ac, char **av)
// {
//     int fd;
//     t_data data;

//     if (ac != 2 || !scene_name_check(av[1]))
//     {
//         printf("Bad arguments : Usage : ./minirt scene.rt");
//         return EXIT_FAILURE;
//     }
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
// 		return (write(2, "File not found\n", 16), EXIT_FAILURE);
//     data = init_all_data(fd);
//     (void) data;
//     return EXIT_SUCCESS;
// }

typedef struct s_env{
    t_tuple gravity;
    t_tuple wind;
}               t_env;

typedef struct s_projectile{
    t_tuple position;
    t_tuple velocity;
}               t_projectile;

void	put_pixel(t_win *win, int x, int y, int color)
{
	char	*dst;

  if ((x > SIZE_X || x < 0)|| (y > SIZE_Y || y < 0)) 
    return ;
	dst = win->addr + (y * win->line_length + x
			* (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void tick(t_win *win)
{
    t_projectile pro;
    t_env env;
    
    pro.position.x = 0;
    pro.position.y = 1;
    pro.position.z = 0;
    pro.position.w = 1;

    pro.velocity.x = 1;
    pro.velocity.y = 1.8;

    pro.velocity.z = 0;
    pro.velocity.w = 0;
    
    env.gravity.x = 0;
    env.gravity.y = -0.1;
    env.gravity.z = 0;
    env.gravity.w = 0;
    
    env.wind.x = -0.01;
    env.wind.y = 0;
    env.wind.z = 0;
    env.wind.w = 0;

    int i;

    i = 0;
    pro.velocity = ft_normalization(pro.velocity);
    pro.velocity = ft_mult_vector(pro.velocity, 11.25);
    while (pro.position.y > 0)
    {
        put_pixel(win, pro.position.x, SIZE_Y - pro.position.y, 0xFFFFFF);
        pro.position = ft_sum_tuple(pro.position, pro.velocity);
        pro.velocity = ft_sum_tuple(pro.velocity, ft_sum_tuple(env.gravity, env.wind));
        i++;
    }
    mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0 );
}

int exit_window(t_win *win)
{
  // mlx_destroy_image(fractal->mlx, fractal->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	exit(1);
	return (0);
}

t_win *init_mlx(void)
{
  t_win *win;
  
  win = malloc(sizeof(t_win));
  win->mlx = mlx_init();
  win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
  win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
  win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
  return (win);
}

int main()
{
  t_win *win;

  win = init_mlx();
  tick(win);
  mlx_hook(win->win, 17, 0L, exit_window, win);
  mlx_loop(win->mlx);
  return (0);
}