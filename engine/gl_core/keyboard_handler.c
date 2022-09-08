/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:40:57 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 17:28:10 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gl_device.h"
#include "gl_engine.h"
#include "gl_input.h"

extern int	input_key_get_index(int key_code);

int	handle_key_press(int key_code, void *param)
{
	t_device	*device;
	int			key_index;

	device = param;
	printf("(key pressed): keycode = %d\n", key_code);
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
	printf("key released\n");
	key_index = input_key_get_index(key_code);
	if (key_index != -1)
	{
		device->input.key_state[key_index] = E_INPUT_UN_PRESSED;
	}
	return (0);
}
