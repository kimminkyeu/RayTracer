/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/07 17:17:13 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"
#include "gl_input.h"
#include "main.h"
/** TODO: mouse 이동에 대한 감지를 좀 더 잘 할 수 있는 방법이 없을까... */

int	render_viewport(t_device *device, t_image *viewport)
{		
	/** NOTE: Use Static Variable for private data member! */
	static	t_vec2 pressed_location;
	static	t_vec2 second_location;
	static	int	lock = 0;

	if (input_is_mouse_down(device, MOUSE_RIGHT_CLICK))
	{
		if (lock == 0)
		{
			pressed_location = input_get_mouse_pos(device);
			lock = 1;
		}
		second_location = input_get_mouse_pos(device);
		gl_draw_line(viewport, pressed_location, second_location, WHITE);
		pressed_location = second_location;
	}
	else if (input_is_mouse_unpressed(device, MOUSE_RIGHT_CLICK))
	{
		/** test = GREEN; */
		if (pressed_location.x == second_location.x && pressed_location.y == second_location.y)
			printf("Simple Press\n");
		else
			printf("\t#Mouse-moved (%f / %f) -> (%f / %f)\n", pressed_location.x, pressed_location.y, second_location.x, second_location.y);
		lock = 0;
	}
	return (0);
}

