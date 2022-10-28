/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 21:31:20 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "main.h"
#include "thread.h"

static void fill_low_resolution_pixel(t_device *device, int x, int y, int argb)
{
	int		k;
	int 	j;
	float	dx;

	dx = 1.0f / device->renderer_settings.resolution_ratio;
	k = 0;
	while (k < dx)
	{
		j = 0;
		while (j < dx)
		{
			*gl_get_pixel_addr(device->screen_image, x * dx + j, y * dx + k) \
				= argb;
			j++;
		}
		k++;
	}
}

void copy_pixel_buffer_to_screen_image(t_device *device)
{
	int	x;
	int	y;
	int	pixel_color;

	y = 0;
	while (y < device->pixel_image->img_size.height)
	{
		x = 0;
		while (x < device->pixel_image->img_size.width)
		{
			pixel_color = gl_get_pixel_color_int(device->pixel_image, x, y);
			fill_low_resolution_pixel(device, x, y, pixel_color);
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
	int y = -1;
	int x = 0;

	const int num_of_thread = data->info->thread_num;
	while ((data->id + (y * num_of_thread)) < height)
	{
		x = -1;
		while (++x < width)
		{
			gl_draw_pixel(img, x, (data->id + (y * num_of_thread)), \
				do_ray_tracing_and_return_color(device, img, x, \
								(data->id + (y * num_of_thread))));
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
	if (device->is_high_resolution_render_mode == false && device->renderer_settings.resolution_ratio != 1)
		return (false);
	else
		return (true);
}

void create_thread_and_update_each(t_device *device)
{
	int i = 0;
	while (i < device->thread_info.thread_num)
	{
		device->thread_info.thread_group[i].id = i;
		device->thread_info.thread_group[i].device = device;

		if (!is_high_resolution_mode(device))
			device->thread_info.thread_group[i].image = device->pixel_image;
		else
			device->thread_info.thread_group[i].image = device->screen_image;
		device->thread_info.thread_group[i].info = &device->thread_info;
		pthread_create(&(device->thread_info.thread_group[i].thread), NULL, thread_update, &(device->thread_info.thread_group[i]));
		i++;
	}
}

int	update(t_device *device)
{
	const long long render_start_time = get_time_ms();
	int				i;

	device->thread_info.finished_thread_num = 0;
	if (is_high_resolution_mode(device))
		gl_draw_background(device->screen_image, BLACK);
	create_thread_and_update_each(device);
	if (!is_high_resolution_mode(device))
	{
		i = -1;
		while (++i < device->thread_info.thread_num)
			pthread_join(device->thread_info.thread_group[i].thread, NULL);
		copy_pixel_buffer_to_screen_image(device);
		engine_push_image_to_window(device, device->screen_image, 0, 0);
	}
	else
	{
		printf("# Rendering...\n\n");
		while (device->thread_info.finished_thread_num != device->thread_info.thread_num)
			engine_push_image_to_window(device, device->screen_image, 0, 0);
		printf("# Total %d threads has finished it's work\n\n", device->thread_info.finished_thread_num);
	}
	draw_render_time(device, get_time_ms() - render_start_time, gl_vec2_2f(30, 30), WHITE);
	return (0);
}
