/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/08/22 12:35:09 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	put_pixel(t_win *win, int x, int y, unsigned int color)
{
	char	*dst;

	if ((x > SIZE_X || x < 0) || (y > SIZE_Y || y < 0))
		return ;
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_free_all(t_complete **complete)
{
	free_data(&(*complete)->data, (*complete)->win->mlx);
}

int	exit_window(t_complete *complete)
{
	t_win	*win;

	win = (t_win *)complete->win;
	ft_free_all(&complete);
	mlx_clear_window(complete->win->mlx, complete->win->win);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	free(complete);
	exit(0);
	return (0);
}

t_win	*init_mlx(void)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	if (!win)
		return (NULL);
	win->mlx = mlx_init();
	if (!win->mlx)
		return (NULL);
	win->img = mlx_new_image(win->mlx, SIZE_X, SIZE_Y);
	win->win = mlx_new_window(win->mlx, SIZE_X, SIZE_Y, "MiniRT");
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
	return (win);
}

int	main(int ac, char **av)
{
	t_norme_main	v;

	if (ac != 2 || !scene_name_check(av[1]))
		return (printf("Bad arguments : Usage : ./minirt scene.rt\n"),
			EXIT_FAILURE);
	v.fd = open(av[1], O_RDONLY);
	if (v.fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
	v.win = init_mlx();
	if (!v.win)
		return (EXIT_FAILURE);
	v.data = init_all_data(v.fd, v.win->mlx);
	if (!v.data)
		return (free_win_classic(v.win), EXIT_FAILURE);
	v.complete = malloc(sizeof(t_complete));
	if (!v.complete)
		return (free_data(&v.data, v.win->mlx), free_win_classic(v.win),
			EXIT_FAILURE);
	v.complete->data = v.data;
	v.complete->win = v.win;
	start_threads(v.complete);
	mlx_put_image_to_window(v.win->mlx, v.win->win, v.win->img, 0, 0);
	setup_hooks(v.win, v.complete);
	mlx_loop(v.win->mlx);
	return (EXIT_SUCCESS);
}
