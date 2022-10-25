/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:44:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 06:00:22 by minkyeki         ###   ########.fr       */
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
