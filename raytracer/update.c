/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 22:40:39 by minkyeki         ###   ########.fr       */
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

void copy_pixel_buffer_to_screen_image(t_device *device)
{
	int x = 0;
	int y = 0;
	int k = 0;
	int j = 0;
	while (y < device->pixel_image->img_size.height)
	{
		x = 0;
		while (x < device->pixel_image->img_size.width)
		{
			int pixel_color = gl_get_pixel_color_int(device->pixel_image, x, y);

			k = 0;
			while (k < device->resolution_ratio)
			{
				j = 0;
				while (j < device->resolution_ratio)
				{
					*gl_get_pixel_addr(device->screen_image, x * device->resolution_ratio + j, y * device->resolution_ratio + k) = pixel_color;
					j++;
				}
				k++;
			}
			x++;
		}
		y++;
	}
}

void *thread_update(void *arg)
{
	t_thread *data = arg;
	t_image  *img = data->image;
	t_device *device = data->device;

	const int width = img->img_size.width;
	const int height = img->img_size.height;
	int y = 0;
	int x = 0;

	const int num_of_thread = data->info->thread_num;
	while ((data->id + (y * num_of_thread)) < height)
	{
		x = 0;
		while (x < width) // draw each row
		{
			const int final_color = do_ray_tracing_and_return_color(device, img, x, (data->id + (y * num_of_thread)));
			gl_draw_pixel(img, x, (data->id + (y * num_of_thread)), final_color);
			x++;
		}
		y++;
	}

	pthread_mutex_lock(&(data->info->finished_num_mutex));
	data->info->finished_thread_num += 1;
	pthread_mutex_unlock(&(data->info->finished_num_mutex));
	return (NULL);
}

static void draw_render_time(t_device *device, long long time, t_vec2 location, int argb)
{
	char	*str;

	mlx_string_put(device->mlx, device->win, location.x, location.y, argb, "Last render(ms)");
	mlx_string_put(device->mlx, device->win, location.x, location.y + 20, argb, ":");
	str = ft_itoa(time);
	mlx_string_put(device->mlx, device->win, location.x + 12, location.y + 20, argb, str);
	free(str);
}

bool is_high_resolution_mode(t_device *device)
{
	if (device->is_high_resolution_render_mode == false && device->resolution_ratio != 1)
		return (false);
	else
		return (true);
}

int	update(t_device *device)
{
	long long render_start_time;
	long long render_end_time;

	render_start_time = get_time_ms();
	device->thread_info.finished_thread_num = 0;

	int i = 0;
	while (i < device->thread_info.thread_num)
	{
		device->thread_info.thread_group[i].id = i;
		device->thread_info.thread_group[i].device = device;

		if (!is_high_resolution_mode(device))
			device->thread_info.thread_group[i].image = device->pixel_image;
		else // if not High_Res mode
			device->thread_info.thread_group[i].image = device->screen_image;

		device->thread_info.thread_group[i].info = &device->thread_info;
		pthread_create(&(device->thread_info.thread_group[i].thread), NULL, thread_update, &(device->thread_info.thread_group[i]));
		i++;
	}

	if (!is_high_resolution_mode(device)) // if Low-res mode, wait until every thread is finished.
	{
		i = -1;
		while (++i < device->thread_info.thread_num)
			pthread_join(device->thread_info.thread_group[i].thread, NULL);
		copy_pixel_buffer_to_screen_image(device); // copy pixel_image_buffer to screen_image
		engine_push_image_to_window(device, device->screen_image, 0, 0);
	}
	else
	{   // if high_res mode, then push image to screen every time.
		while (device->thread_info.finished_thread_num != device->thread_info.thread_num)
			engine_push_image_to_window(device, device->screen_image, 0, 0);
	}
	render_end_time = get_time_ms();
	draw_render_time(device, render_end_time - render_start_time, gl_vec2_2f(30, 30), WHITE);
	return (0);
}
