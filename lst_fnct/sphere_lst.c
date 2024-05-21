/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vk <vk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:12:03 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/21 22:50:08 by vk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void sphere_lstfree(t_sphere **lst)
{
  t_sphere	*tmp;

  if (!lst)
    return ;
  while (*lst)
  {
    tmp = (*lst)->next;
    free(*lst);
    *lst = tmp;
  }
}

t_sphere	*sphere_lstlast(t_sphere *lst)
{
	if (!lst)
		return (NULL);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

int	sphere_lstsize(t_sphere *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i + 1);
}

void	sphere_lstadd_back(t_sphere **lst, t_sphere *new)
{
	t_sphere	*tmp;

	tmp = NULL;
	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = sphere_lstlast((*lst));
		tmp->next = new;
	}
	else
		*lst = new;
}
