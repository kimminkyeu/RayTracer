/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:23:24 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 22:23:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "main.h"
#include "thread.h"

void	create_thread_and_update_each(t_device *device)
{
	int	i;

	i = -1;
	while (++i < device->thread_info.thread_num)
	{
		device->thread_info.thread_group[i].id = i;
		device->thread_info.thread_group[i].device = device;
		if (!is_high_resolution_mode(device))
			device->thread_info.thread_group[i].image = device->pixel_image;
		else
			device->thread_info.thread_group[i].image = device->screen_image;
		device->thread_info.thread_group[i].info = &device->thread_info;
		pthread_create(&(device->thread_info.thread_group[i].thread), \
		NULL, thread_update, &(device->thread_info.thread_group[i]));
	}
}

void	thread_trace_ray_and_fill_pixel(t_thread *data, \
						t_device *device, t_image *img)
{
	const int	num_of_thread = data->info->thread_num;
	const int	width = img->img_size.width;
	const int	height = img->img_size.height;
	int			y;
	int			x;

	y = -1;
	while ((data->id + (++y * num_of_thread)) < height)
	{
		x = -1;
		while (++x < width)
		{
			gl_draw_pixel(img, x, (data->id + (y * num_of_thread)), \
				do_ray_tracing_and_return_color(device, img, x, \
								(data->id + (y * num_of_thread))));
		}
	}
}

void	*thread_update(void *arg)
{
	t_thread *const	data = arg;
	t_image *const	img = data->image;
	t_device *const	device = data->device;

	thread_trace_ray_and_fill_pixel(data, device, img);
	pthread_mutex_lock(&(data->info->finished_num_mutex));
	data->info->finished_thread_num += 1;
	pthread_mutex_unlock(&(data->info->finished_num_mutex));
	return (NULL);
}
