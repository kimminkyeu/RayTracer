/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:40:57 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:16:25 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gl_device.h"
#include "gl_engine.h"
#include "gl_input.h"


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
