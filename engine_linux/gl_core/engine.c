/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:16:30 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/04 22:31:30 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	engine_push_image(t_device *device, t_image *image, int x, int y)
{
	if (x <= device->win_width && x >= 0 && y <= device->win_height && y >= 0)
		if (device != NULL && image != NULL && image->img_ptr != NULL)
			mlx_put_image_to_window(device->mlx, device->win, image->img_ptr, x, y);
}

void	engine_exit(t_device *device, bool is_error)
{
	if (device != NULL && device->viewport.img_ptr != NULL)
		mlx_destroy_image(device->mlx, device->viewport.img_ptr);

	if (device != NULL && device->panel.img_ptr != NULL)
		mlx_destroy_image(device->mlx, device->panel.img_ptr);

	if (device->win != NULL)
		mlx_destroy_window(device->mlx, device->win);

	if (device != NULL && device->mlx != NULL)
		free(device->mlx);

	if (device != NULL)
		free(device);

	if (is_error == ERROR)
		exit(EXIT_FAILURE); 
	else
		exit(EXIT_SUCCESS);
}

void	engine_new_image(t_image *image, void* mlx_ptr, int _width, int _height)
{
	if (_width <= 0 || _height <= 0)
		return ;
	if (image->img_ptr == NULL && mlx_ptr != NULL)
	{
		image->img_ptr = mlx_new_image(mlx_ptr, _width, _height);
		image->addr = mlx_get_data_addr(image->img_ptr, \
				&(image->bits_per_pixel), \
				&(image->line_length), &(image->endian));
		image->width = _width;
		image->height = _height;
	}
	printf("New image created. --> [%dpx/%dpx]\n", _width, _height);
}

t_device	*engine_init(int _viewport_width, int _panel_width, int _win_height, char *title)
{
	t_device	*device;

	device = ft_calloc(1, sizeof(*device));
	if (device == NULL)
		engine_exit(device, ERROR);
	device->mlx = mlx_init();
	if (device->mlx == NULL)
		engine_exit(device, ERROR);

	device->win_width = _viewport_width + _panel_width;
	device->win_height = _win_height;
		
	device->win = mlx_new_window(device->mlx, device->win_width, device->win_height, title);
	if (device->win == NULL)
		engine_exit(device, ERROR);


	/** NOTE: Viewport */
	engine_new_image(&device->viewport, device->mlx, _viewport_width, _win_height);

	/** NOTE: Control Panel*/
	engine_new_image(&device->panel, device->mlx, _panel_width, _win_height);

	/** initialize device input data */
	input_init(&device->input);

	engine_set_key_event(device, handle_key_press, handle_key_release);
	engine_set_mouse_event(device, handle_mouse_press, handle_mouse_release);


	return (device);
}

int		handle_exit(t_device *device)
{
	ft_putstr_fd("Closing Programm....\n", STDOUT);
	engine_exit(device, SUCCESS);
	return (0);
}

void	engine_start_loop(t_device *device, int (*render_layer)())
{
	mlx_hook(device->win, ON_DESTROY, 0, handle_exit, device);
	mlx_loop_hook(device->mlx, render_layer, device);
	mlx_loop(device->mlx);
}

/** NOTE: if handler changes, reset engine */
void		engine_set_key_event(t_device *device, int (*f_key_press)(), int (*f_key_release)())
{
	if (device != NULL && f_key_press != NULL && f_key_release != NULL)
	{
		mlx_hook(device->win, ON_KEY_PRESS, KeyPressMask, f_key_press, device);
		mlx_hook(device->win, ON_KEY_RELEASE, KeyReleaseMask, f_key_release, device);
	}
}

void		engine_set_mouse_event(t_device *device, int (*f_mouse_press)(), int (*f_mouse_release)())
{
	if (device != NULL && f_mouse_press != NULL && f_mouse_release != NULL)
	{
		mlx_hook(device->win, ON_MOUSE_PRESS, ButtonPressMask, f_mouse_press, device);
		mlx_hook(device->win, ON_MOUSE_RELEASE, ButtonReleaseMask, f_mouse_release, device);
	}
}


