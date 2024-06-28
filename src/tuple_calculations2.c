/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_calculations2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:07:22 by udumas            #+#    #+#             */
/*   Updated: 2024/06/27 10:06:05 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_comp_float(float n1, float n2)
{
	if (fabs(n1 - n2) < EPSILON)
		return (1);
	else
		return (0);
}

int	same_tuple(t_tuple t1, t_tuple t2)
{
	if (t1.x != t2.x)
		return (0);
	if (t1.y != t2.y)
		return (0);
	if (t1.z != t2.z)
		return (0);
	if (t1.w != t2.w)
		return (0);
	return (1);
}

float	ft_magnitude(t_tuple v)
{
    float magnititude;

    magnititude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return (magnititude);
}

t_tuple	ft_normalization(t_tuple v)
{
	float	magnitude;
	t_tuple	new;

	magnitude = ft_magnitude(v);
	if (magnitude == 0)
		return (v);
	new.x = v.x / magnitude;
	new.y = v.y / magnitude;
	new.z = v.z / magnitude;
	new.w = v.w / magnitude;
	return (new);
}

float	ft_dotproduct(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

t_tuple cross_product(t_tuple v1, t_tuple v2)
{
    t_tuple new;
    
    new.w = 0;
    new.x = v1.y * v2.z - v1.z * v2.y;
    new.y = v1.z * v2.x - v1.x * v2.z;
    new.z = v1.x * v2.y - v1.y * v2.x;
    return (new);
}
