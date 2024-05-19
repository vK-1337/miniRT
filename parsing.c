/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:52 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/19 19:05:22 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int scene_name_check(char *av)
{
    int i;

    if (!av)
        return (0);
    i = 0;
    while (av[i])
        i++;
    if (i <= 1)
        return (0);
    if (av[i - 1] != 't' && av[i - 2] != 'r' && av[i - 3] != '.')
        return (0);
    if (!av[i - 4])
        return (0);
    return (1);
}
