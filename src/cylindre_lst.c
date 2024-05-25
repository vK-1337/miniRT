/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:11:43 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/25 12:12:26 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_cylindre	*cylindre_lstlast(t_cylindre *lst)
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

int	cylindre_lstsize(t_cylindre *lst)
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

void	cylindre_lstadd_back(t_cylindre **lst, t_cylindre *new)
{
	t_cylindre	*tmp;

	tmp = NULL;
	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = cylindre_lstlast((*lst));
		tmp->next = new;
	}
	else
		*lst = new;
}

void cylindre_lstfree(t_cylindre **lst)
{
  t_cylindre	*tmp;

  if (!lst)
    return ;
  while (*lst)
  {
    tmp = (*lst)->next;
    free(*lst);
    *lst = tmp;
  }
  free(lst);
}

