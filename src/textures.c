/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:01:11 by vda-conc          #+#    #+#             */
/*   Updated: 2024/06/13 14:07:14 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void *ft_init_image(t_sphere *sphere, t_win *win)
{
    Image *texture_image;

    Image* texture_image = load_xpm_image(window.mlx_ptr, sphere->texture_path);

}