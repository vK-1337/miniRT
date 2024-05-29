/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:42:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/29 17:50:13 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_tuple ft_reflect(t_tuple in, t_tuple normal)
{
    return (ft_dif_tuple(in, ft_mult_vector(normal, 2 * ft_dotproduct(in, normal))));
}
