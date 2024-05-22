/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_canon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:07:49 by udumas            #+#    #+#             */
/*   Updated: 2024/05/22 20:19:07 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

typedef struct s_env{
    t_tuple gravity;
    t_tuple wind;
}               t_env;

typedef struct s_projectile{
    t_tuple position;
    t_tuple velocity;
}               t_projectile;

int main()
{
    t_projectile pro;
    t_env env;
    
    pro.position.x = 0;
    pro.position.y = 1;
    pro.position.z = 0;
    pro.position.w = 1;

    pro.velocity.x = 10;
    pro.velocity.y = 2;
    pro.velocity.z = 0;
    pro.velocity.w = 0;
    
    env.gravity.x = 0;
    env.gravity.y = -0.1;
    env.gravity.z = 0;
    env.gravity.w = 0;
    
    env.wind.x = -0.01;
    env.wind.y = 0;
    env.wind.z = 0;
    env.wind.w = 0;

    int i;

    i = 0;
    while (pro.position.y > 0)
    {
        printf("position at %d tick\nx = %f\ny = %f\n", i, pro.position.x, pro.position.y);
        pro.position = ft_sum_tuple(pro.position, pro.velocity);
        pro.velocity = ft_sum_tuple(pro.velocity, ft_sum_tuple(env.gravity, env.wind));
        usleep(100000);
        i++;
    }
    printf("position at %d tick\nx = %f\ny = %f\n", i, pro.position.x, pro.position.y);
}