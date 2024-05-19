/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:09:55 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/19 19:43:53 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
    int fd;
    t_data data;

    if (ac != 2 || !scene_name_check(av[1]))
    {
        printf("Bad arguments : Usage : ./minirt scene.rt");
        return EXIT_FAILURE;
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
		return (write(2, "File not found\n", 16), EXIT_FAILURE);
    data = init_all_data(fd);
    return EXIT_SUCCESS;
}