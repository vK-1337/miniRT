/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:07:30 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 16:09:54 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
