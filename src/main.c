/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 14:11:38 by vda-conc         ###   ########.fr       */
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

void	destroy_t_win(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
}

void	start_threads(t_complete *complete)
{
	int	i;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = 0;
	start_y = 0;
	end_x = SIZE_X / 10;
	end_y = SIZE_Y / 10;
	complete->thread = malloc(sizeof(t_thread) * (10 * 10));
	if (!complete->thread)
		return ;
	complete->data->pixel_put = malloc(sizeof(pthread_mutex_t));
	if (!complete->data->pixel_put)
		return ;
	pthread_mutex_init(complete->data->pixel_put, NULL);
	i = 0;
	while (i < 10 * 10)
	{
		complete->thread[i].start_x = start_x;
		complete->thread[i].start_y = start_y;
		complete->thread[i].end_x = end_x;
		complete->thread[i].end_y = end_y;
		complete->thread[i].index = i;
		complete->thread[i].win = complete->win;
		complete->thread[i].data = complete->data;
		pthread_create(&complete->thread[i].pthread_id, NULL, render,
			&complete->thread[i]);
		start_x = end_x;
		end_x += SIZE_X / 10;
		if (start_x == SIZE_X)
		{
			start_x = 0;
			end_x = SIZE_X / 10;
			start_y = end_y;
			end_y += SIZE_Y / 10;
		}
		if (start_y == SIZE_Y)
		{
			start_y = i * SIZE_Y / 10;
			end_y = start_y + SIZE_Y / 10;
		}
		if (end_x > SIZE_X)
			end_x = SIZE_X;
		if (end_y > SIZE_Y)
			end_y = SIZE_Y;
		i++;
	}
	i--;
	while (i >= 0)
	{
		pthread_join(complete->thread[i].pthread_id, NULL);
		i--;
	}
	free(complete->thread);
	pthread_mutex_destroy(complete->data->pixel_put);
	free(complete->data->pixel_put);
}

int	key_hook(int keycode, t_complete *complete)
{
	if (keycode == XK_Escape)
		exit_window(complete);
	return (0);
}

void	setup_hooks(t_win *win, t_complete *complete)
{
	mlx_key_hook(win->win, key_hook, complete);
	mlx_hook(win->win, 17, 0, exit_window, complete);
}

void	free_win_classic(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
}

int	main(int ac, char **av)
{
	int			fd;
	t_world		*data;
	t_win		*win;
	t_complete	*complete;

	if (ac != 2 || !scene_name_check(av[1]))
		return (printf("Bad arguments : Usage : ./minirt scene.rt\n"),
			EXIT_FAILURE);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
	win = init_mlx();
	if (!win)
		return (EXIT_FAILURE);
	data = init_all_data(fd, win->mlx);
	if (!data)
		return (free_win_classic(win), EXIT_FAILURE);
	complete = malloc(sizeof(t_complete));
	if (!complete)
		return (free_data(&data, win->mlx), free_win_classic(win),
			EXIT_FAILURE);
	complete->data = data;
	complete->win = win;
	start_threads(complete);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	setup_hooks(win, complete);
	mlx_loop(win->mlx);
	return (EXIT_SUCCESS);
}
