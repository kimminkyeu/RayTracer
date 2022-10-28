/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:20:14 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:20:15 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gl_device.h"
#include "gl_engine.h"
#include "gl_input.h"

extern int	input_key_get_index(int key_code);
extern int	handle_exit(t_device *device);

int	handle_key_press(int key_code, void *param)
{
	t_device	*device;
	int			key_index;

	device = param;
	if (key_code == KEY_ESC)
	{
		printf("ESC pressed\n");
		engine_exit(device, SUCCESS);
	}
	else
	{
		key_index = input_key_get_index(key_code);
		if (key_index != -1)
		{
			device->input.key_state[key_index] = E_INPUT_IS_PRESSED;
		}
	}
	return (0);
}

int	handle_key_release(int key_code, void *param)
{
	t_device	*device;
	int			key_index;

	device = param;
	key_index = input_key_get_index(key_code);
	if (key_index != -1)
	{
		device->input.key_state[key_index] = E_INPUT_UN_PRESSED;
	}
	return (0);
}

void	engine_set_key_event(t_device *device, int (*f_key_press)(), \
								int (*f_key_release)())
{
	if (device == NULL)
		return ;
	mlx_hook(device->win, ON_DESTROY, 0, handle_exit, device);
	if (f_key_press != NULL)
		mlx_hook(device->win, ON_KEY_PRESS, KeyPressMask, \
					f_key_press, device);
	if (f_key_release != NULL)
		mlx_hook(device->win, ON_KEY_RELEASE, KeyReleaseMask, \
					f_key_release, device);
}

int	input_is_key_down(t_device *device, int key_code)
{
	int	key_state;
	int	index;

	index = input_key_get_index(key_code);
	key_state = device->input.key_state[index];
	if (key_state == E_INPUT_IS_PRESSED)
	{
		return (true);
	}
	else
		return (false);
}

int	input_is_key_unpressed(t_device *device, int key_code)
{
	int	key_state;
	int	index;

	index = input_key_get_index(key_code);
	key_state = device->input.key_state[index];
	if (key_state == E_INPUT_UN_PRESSED)
	{
		device->input.key_state[index] = E_INPUT_NO_STATE;
		return (true);
	}
	else
		return (false);
}
