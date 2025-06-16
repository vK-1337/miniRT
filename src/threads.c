/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:54:34 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 21:56:37 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	start_threads(t_complete *complete)
{
	t_norme_threads	v;

	v.start_x = 0;
	v.start_y = 0;
	v.end_x = SIZE_X / 10;
	v.end_y = SIZE_Y / 10;
	complete->thread = malloc(sizeof(t_thread) * (10 * 10));
	if (!complete->thread)
		return ;
	complete->data->pixel_put = malloc(sizeof(pthread_mutex_t));
	if (!complete->data->pixel_put)
		return ;
	pthread_mutex_init(complete->data->pixel_put, NULL);
	ft_start_thread_helper2(&v, complete);
	free(complete->thread);
	pthread_mutex_destroy(complete->data->pixel_put);
	free(complete->data->pixel_put);
}

void	ft_start_thread_helper2(t_norme_threads *v, t_complete *complete)
{
	v->i = 0;
	while (v->i < 10 * 10)
	{
		thread_attribution(&complete->thread[v->i], complete, v);
		pthread_create(&complete->thread[v->i].pthread_id, NULL, render,
			&complete->thread[v->i]);
		ft_start_thread_helper(v);
		v->i++;
	}
	v->i--;
	while (v->i >= 0)
	{
		pthread_join(complete->thread[v->i].pthread_id, NULL);
		v->i--;
	}
}

void	ft_start_thread_helper(t_norme_threads *v)
{
	v->start_x = v->end_x;
	v->end_x += SIZE_X / 10;
	if (v->start_x == SIZE_X)
	{
		v->start_x = 0;
		v->end_x = SIZE_X / 10;
		v->start_y = v->end_y;
		v->end_y += SIZE_Y / 10;
	}
	if (v->start_y == SIZE_Y)
	{
		v->start_y = v->i * SIZE_Y / 10;
		v->end_y = v->start_y + SIZE_Y / 10;
	}
	if (v->end_x > SIZE_X)
		v->end_x = SIZE_X;
	if (v->end_y > SIZE_Y)
		v->end_y = SIZE_Y;
}

void	thread_attribution(t_thread *thread, t_complete *complete,
		t_norme_threads *v)
{
	thread->start_x = v->start_x;
	thread->start_y = v->start_y;
	thread->end_x = v->end_x;
	thread->end_y = v->end_y;
	thread->index = v->i;
	thread->win = complete->win;
	thread->data = complete->data;
}
