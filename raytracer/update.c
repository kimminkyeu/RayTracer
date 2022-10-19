/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 23:12:25 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <pthread.h>
// #include <unistd.h>
// #include "gl_engine.h"
// #include "objects.h"
// #include "gl_color.h"
// #include "gl_draw.h"
// #include "gl_dvec3.h"
// #include "gl_vec4.h"
// #include "gl_vec3.h"
// #include "gl_vec2.h"
// #include "libft.h"
#include "trace_ray.h"
#include "main.h"
#include "thread.h"

void *thread_update(void *arg)
{
	t_thread *data = arg;
	t_image  *img = data->image;
	t_device *device = data->device;

	const int width = img->img_size.width;
	const int height = img->img_size.height;
	int y = 0;
	int x = 0;

	/* NOTE: 디버깅을 위해서 일단 싱글쓰레드로 변경함.*/
	while (data->id == 1 && y < height)
	{
		x = -1;
		while (x < width)
		{
			const int final_color = do_ray_tracing_and_return_color(device, img, x, y);
			gl_draw_pixel(img, x, y, final_color);
			x++;
		}
		y++;
	}


	// const int num_of_thread = data->info->thread_num;
	// while ((data->id + (y * num_of_thread)) < height)
	// {
	// 	x = 0;
	// 	while (x < width) // draw each row
	// 	{
	// 		const int final_color = do_ray_tracing_and_return_color(device, img, x, (data->id + (y * num_of_thread)));
	// 		gl_draw_pixel(img, x, (data->id + (y * num_of_thread)), final_color);
	// 		x++;
	// 	}
	// 	y++;
	// }


	pthread_mutex_lock(&(data->info->finished_num_mutex));
	data->info->finished_thread_num += 1;
	pthread_mutex_unlock(&(data->info->finished_num_mutex));
	return (NULL);
}

int	update(t_device *device, t_image *img)
{
	printf("\033[36m\n[THREAD TEST] --> total thread count = %d\033[0m\n", device->thread_info.thread_num);
	// THREAD TEST (구조는 나중에 개선하기.)
	int i = 0;
	while (i < device->thread_info.thread_num)
	{
		device->thread_info.thread_group[i].id = i;
		device->thread_info.thread_group[i].device = device;
		device->thread_info.thread_group[i].image = img;
		device->thread_info.thread_group[i].info = &device->thread_info;
		pthread_create(&(device->thread_info.thread_group[i].thread), NULL, thread_update, &(device->thread_info.thread_group[i]));
		pthread_detach(device->thread_info.thread_group[i].thread);
		i++;
	}
	ft_putstr_fd("\033[36m\n[Threads has been created]\033[0m\n", 0);
	return (0);
}
