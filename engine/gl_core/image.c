/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:10:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:12:06 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>

#include "libft.h"
#include "lights.h"
#include "camera.h"
#include "gl_engine.h"
#include "gl_vec2.h"

t_image	*engine_new_image(t_device *device, t_vec2 img_size, \
							t_vec2 img_location)
{
	t_image	*new_image;

	new_image = ft_calloc(1, sizeof(*new_image));
	if (img_size.width <= 0 || img_size.height <= 0)
		return (NULL);
	if (device->mlx != NULL)
	{
		new_image->img_ptr = mlx_new_image(device->mlx, \
											img_size.width, img_size.height);
		new_image->addr = mlx_get_data_addr(new_image->img_ptr, \
				&(new_image->bits_per_pixel), \
				&(new_image->line_length), &(new_image->endian));
		new_image->mlx_ptr = device->mlx;
		new_image->img_size = img_size;
		new_image->img_location = img_location;
		new_image->device_ptr = device;
	}
	printf("engine_new_image() : W(%f) H(%f)\n", \
			new_image->img_size.width, new_image->img_size.height);
	return (new_image);
}

t_image	*engine_new_xpm_image(t_device *device, char *filename, \
								t_vec2 img_location)
{
	t_image	*new_image;
	int		width;
	int		height;

	if (device == NULL || filename == NULL)
		return (NULL);
	new_image = ft_calloc(1, sizeof(*new_image));
	new_image->img_ptr = mlx_xpm_file_to_image(device->mlx, \
							filename, &width, &height);
	new_image->img_size.width = width;
	new_image->img_size.height = height;
	new_image->mlx_ptr = device->mlx;
	new_image->device_ptr = device;
	if (new_image->img_ptr == NULL)
	{
		free(new_image);
		return (NULL);
	}
	new_image->addr = mlx_get_data_addr(new_image->img_ptr, \
				&(new_image->bits_per_pixel), \
				&(new_image->line_length), &(new_image->endian));
	new_image->img_location = img_location;
	return (new_image);
}

void	destory_images(t_device *device)
{
	if (device->screen_image != NULL)
	{
		mlx_destroy_image(device->mlx, device->screen_image->img_ptr);
		free(device->screen_image);
	}
	if (device->pixel_image != NULL)
	{
		mlx_destroy_image(device->mlx, device->pixel_image->img_ptr);
		free(device->pixel_image);
	}
}

static bool	is_inside_window(t_device *device, int _x, int _y)
{
	if (_x < device->renderer_settings.win_width && _x >= 0 && \
			_y < device->renderer_settings.win_height && _y >= 0)
	{
		return (true);
	}
	else
		return (false);
}

void	engine_push_image_to_window(t_device *device, t_image *image, \
									int x, int y)
{
	if (is_inside_window(device, x, y))
	{
		if (device != NULL && image != NULL && image->img_ptr != NULL)
		{
			mlx_put_image_to_window(device->mlx, device->win, \
									image->img_ptr, x, y);
		}
	}
}
