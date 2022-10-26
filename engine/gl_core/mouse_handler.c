/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:44:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:29:40 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gl_engine.h"
#include "gl_input.h"

extern int	input_mouse_get_index(int key_code);

int	handle_mouse_press(int key_code, int x, int y, void *param)
{
	t_device	*device;
	int			key_index;

	(void)x;
	(void)y;
	device = param;
	key_index = input_mouse_get_index(key_code);
	if (key_index != -1)
	{
		device->input.mouse_state[key_index] = E_INPUT_IS_PRESSED;
	}
	return (0);
}

int	handle_mouse_release(int key_code, int x, int y, void *param)
{
	t_device	*device;
	int			key_index;

	(void)x;
	(void)y;
	device = param;
	key_index = input_mouse_get_index(key_code);
	if (key_index != -1)
	{
		device->input.mouse_state[key_index] = E_INPUT_UN_PRESSED;
	}
	return (0);
}

void	engine_set_mouse_event(t_device *device, int (*f_mouse_press)(), \
								int (*f_mouse_release)())
{
	if (device == NULL)
		return ;
	if (f_mouse_press != NULL)
		mlx_hook(device->win, ON_MOUSE_PRESS, ButtonPressMask, \
				f_mouse_press, device);
	if (f_mouse_release != NULL)
		mlx_hook(device->win, ON_MOUSE_RELEASE, ButtonReleaseMask, \
				f_mouse_release, device);
}

int	input_is_mouse_down(t_device *device, int key_code)
{
	int	key_state;
	int	index;

	index = input_mouse_get_index(key_code);
	key_state = device->input.mouse_state[index];
	if (key_state == E_INPUT_IS_PRESSED)
	{
		return (true);
	}
	else
		return (false);
}

int	input_is_mouse_unpressed(t_device *device, int key_code)
{
	int	key_state;
	int	index;

	index = input_mouse_get_index(key_code);
	key_state = device->input.mouse_state[index];
	if (key_state == E_INPUT_UN_PRESSED)
	{
		device->input.mouse_state[index] = E_INPUT_NO_STATE;
		return (true);
	}
	else
		return (false);
}
