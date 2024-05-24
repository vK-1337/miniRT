/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:02:58 by udumas            #+#    #+#             */
/*   Updated: 2024/05/22 20:19:07 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple	ft_sum_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple new;

	new.x = t1.x + t2.x;
	new.y = t1.y + t2.y;
	new.z = t1.z + t2.z;
	new.w = t1.w + t2.w;
    return (new);
}

t_tuple	ft_dif_tuple(t_tuple t1, t_tuple t2)
{
	t_tuple new;

	new.x = t1.x - t2.x;
	new.y = t1.y - t2.y;
	new.z = t1.z - t2.z;
	new.w = t1.w - t2.w;
    return (new);
}

t_tuple ft_neg_tuple(t_tuple t)
{
    t_tuple new;

    new.x = -t.x;
	new.y = -t.y;
	new.z = -t.z;
	new.w = -t.w;
	return (new);
}

t_tuple ft_mult_vector(t_tuple v, float scale)
{
	t_tuple new;

	new.x = v.x * scale;
	new.y = v.y * scale;
	new.z = v.z * scale;
	new.w = v.w * scale;
	return (new);
}

t_tuple ft_div_vector(t_tuple v, int scale)
{
	t_tuple new;

	new.x = v.x / scale;
	new.y = v.y / scale;
	new.z = v.z / scale;
	new.w = v.w / scale;
	return (new);
}
