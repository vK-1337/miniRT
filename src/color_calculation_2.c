/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calculation_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:15 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/30 12:00:41 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	*ft_color(float r, float g, float b)
{
	t_color	*new;

	new = malloc(sizeof(t_color));
	if (!new)
		return (NULL);
	new->r = r;
	new->g = g;
	new->b = b;
	return (new);
}
