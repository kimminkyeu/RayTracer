/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:46:26 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 22:54:23 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_device.h"
#include "gl_engine.h"

int	input_mouse_get_index(int key_code)
{
	if (key_code == MOUSE_LEFT_CLICK)
		return (0);
	else if (key_code == MOUSE_MIDDLE_CLICK)
		return (1);
	else if (key_code == MOUSE_RIGHT_CLICK)
		return (2);
	else if (key_code == MOUSE_SCROLL_UP)
		return (3);
	else if (key_code == MOUSE_SCROLL_DOWN)
		return (4);
	else
		return (-1);
}

int	input_key_get_index(int key_code)
{
	if (key_code == KEY_A)
		return (0);
	else if (key_code == KEY_S)
		return (1);
	else if (key_code == KEY_D)
		return (2);
	else if (key_code == KEY_Q)
		return (3);
	else if (key_code == KEY_W)
		return (4);
	else if (key_code == KEY_E)
		return (5);
	else if (key_code == KEY_R)
		return (6);
	else if (key_code == KEY_1)
		return (7);
	else
		return (-1);
}

#if defined (__linux__)
# define PLATFORM_NAME (__LINUX__)

void	wrap_mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
}

#elif defined (__APPLE__)
# define PLATFORM_NAME (__OSX__)

void	wrap_mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	mlx_mouse_get_pos(win_ptr, x, y);
}

#endif

t_vec2	input_get_mouse_pos(const t_device *device)
{
	int		x;
	int		y;
	t_vec2	pos;

	x = 0;
	y = 0;
	wrap_mlx_mouse_get_pos(device->mlx, device->win, &x, &y);
	pos.x = (float)x;
	pos.y = (float)y;
	return (pos);
}
