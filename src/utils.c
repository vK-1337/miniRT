/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:45:44 by vk                #+#    #+#             */
/*   Updated: 2024/05/24 17:34:49 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void free_char_tab(char **tab)
{
  int i;

  i = 0;
  while (tab[i])
  {
    free(tab[i]);
    i++;
  }
  return;
}

int char_tab_len(char **tab)
{
  int i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}
