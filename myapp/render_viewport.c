/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 17:23:13 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"
#include "gl_input.h"
#include "main.h"
/** TODO:  mouse 이동에 대한 감지를 좀 더 잘 할 수 있는 방법이 없을까... */

int	render_viewport(t_device *device, t_image *viewport)
{
	(void)viewport;
	input_is_mouse_down(device, MOUSE_LEFT_CLICK);
	return (0);
	/** NOTE: Use Static Variable for private data member! */
	// static	t_vec2 pressed_location;
	// static	t_vec2 second_location;
	// static	int	lock = -1;
	// static	int color;
	// static	int	r,g,b;

	// // FIXME: 초기화가 모두 0으로 된다. 근데 왜 켜질까?
	// if (input_is_mouse_down(device, MOUSE_LEFT_CLICK))
	// {
	// 	if (lock == 0 || lock == -1)
	// 	{
	// 		pressed_location = input_get_mouse_pos(device);
	// 		lock = 1;
	// 	}
	// 	if (lock == -1)
	// 	{
	// 		r = 255;
	// 		g = 0;
	// 		b = 0;
	// 	}
	// 	second_location = input_get_mouse_pos(device);
	// 	if (r > 0 && b <= 0)
	// 	{
	// 		color = gl_color(BLACK, r--, g++, 0);
	// 	}
	// 	else if (g > 0 && r <= 0)
	// 	{
	// 		color = gl_color(BLACK, 0, g--, b++);
	// 	}
	// 	else if (b > 0 && g <= 0)
	// 	{
	// 		g = 0;
	// 		color = gl_color(BLACK, r++, 0, b--);
	// 	}
	// 	else
	// 	{
	// 		color = gl_color(BLACK, 255, 0, 0);
	// 		r = 255;
	// 		g = 0;
	// 		b = 0;
	// 	}
	// 	gl_draw_line(viewport, pressed_location, second_location, color);
	// 	pressed_location = second_location;
	// }
	// else if (input_is_mouse_unpressed(device, MOUSE_LEFT_CLICK))
	// {
	// 	/** test = GREEN; */
	// 	if (pressed_location.x == second_location.x && pressed_location.y == second_location.y)
	// 		printf("Simple Press\n");
	// 	else
	// 		printf("\t#Mouse-moved (%f / %f) -> (%f / %f)\n", pressed_location.x, pressed_location.y, second_location.x, second_location.y);
	// 	lock = 0;
	// }
	// return (0);
}