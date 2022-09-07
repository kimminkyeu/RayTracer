/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:46:26 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 20:17:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** #include "input.h" */
#include "device.h"
#include "engine.h"

void	input_init(t_input *input)
{
	int	i;
	
	i = 0;
	while (i < 7)
	{
		input->key_state[i] = 0;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		input->mouse_state[i] = 0;
		i++;
	}
}

int	input_mouse_get_index(int key_code)
{
	if (key_code == MOUSE_LEFT_CLICK) return (0);
	else if (key_code == MOUSE_MIDDLE_CLICK) return (1);
	else if (key_code == MOUSE_RIGHT_CLICK) return (2);
	else if (key_code == MOUSE_SCROLL_UP) return (3);
	else if (key_code == MOUSE_SCROLL_DOWN) return (4);
	else return (-1);
}

int	input_key_get_index(int key_code)
{
	if (key_code == KEY_A) return (0);
	else if (key_code == KEY_S) return (1);
	else if (key_code == KEY_D) return (2);
	else if (key_code == KEY_Q) return (3);
	else if (key_code == KEY_W) return (4);
	else if (key_code == KEY_E) return (5);
	else if (key_code == KEY_R) return (6);
	else return (-1);
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

int input_is_key_unpressed(t_device *device, int key_code)
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

int input_is_mouse_unpressed(t_device *device, int key_code)
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

/** NOTE: I Changed mlx_mms/mlx.h source header to support Linux. */
t_vec2	input_get_mouse_pos(const t_device *device)
{
	int	x;
	int	y;
	t_vec2	pos;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(device->win, &x, &y);
	/** mlx_mouse_get_pos(device->mlx, device->win, &x, &y); */
	pos.x = (float)x;
	/** pos.x = (float)x / (float)device->win_width; */
	pos.y = (float)y;
	/** pos.y = (float)y / (float)device->win_height; */
	return (pos);
}
