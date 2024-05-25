/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <udumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:11:41 by vda-conc          #+#    #+#             */
/*   Updated: 2024/05/25 12:02:09 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void plan_lstfree(t_plan **lst)
{
  t_plan	*tmp;

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

t_plan	*plan_lstlast(t_plan *lst)
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

int	plan_lstsize(t_plan *lst)
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

void	plan_lstadd_back(t_plan **lst, t_plan *new)
{
	t_plan	*tmp;

	tmp = NULL;
	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = plan_lstlast((*lst));
		tmp->next = new;
	}
	else
		*lst = new;
}
