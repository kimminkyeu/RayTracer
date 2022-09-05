/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:44:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:16:12 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gl_engine.h"
#include "gl_input.h"

int	handle_mouse_press(int key_code, int x, int y, void *param)
{
	t_device	*device;
	int			key_index;

	(void)x;
	(void)y;
	device = param;
	/** printf("mouse code : %d\n", key_code); */
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
	/** printf("mouse released\n"); */
	key_index = input_mouse_get_index(key_code);
	if (key_index != -1)
	{
		device->input.mouse_state[key_index] = E_INPUT_UN_PRESSED;
	}
	return (0);
}

