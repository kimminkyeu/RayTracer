/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:44:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/15 14:10:28 by minkyeki         ###   ########.fr       */
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
	// FIXME: 일단 프로그램이 시작되면 이 함수가 호출된다. 마우스를 누르지 않았는데도...
	/** printf("mouse code : %d\n", key_code); */
	key_index = input_mouse_get_index(key_code);
	if (key_index != -1)
	{
		printf("handle_mouse_press() : keycode %d\n", key_code);
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
	 	printf("handle_mouse_release() : keycode %d\n", key_code);
		device->input.mouse_state[key_index] = E_INPUT_UN_PRESSED;
	}
	return (0);
}
