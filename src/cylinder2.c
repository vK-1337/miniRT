/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:30:57 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 09:34:42 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_cylinder	*ft_cylinder(void)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->radius = 1;
	cylinder->y_min = 0;
	cylinder->y_max = 3;
	cylinder->matrix = identity_matrix(4);
	cylinder->m = ft_material();
	cylinder->next = NULL;
	return (cylinder);
}
