/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 16:06:57 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx_linux.h"

int	update_func(t_device *device, t_image *img)
{
	(void)device;
	(void)img;
	/** WARN: Use Static Variable for private data member! */
	// t_vec4 color = gl_vec4(0, 10, 30, 0);
	// color = gl_color_set_brightness(color, 10.0f);
	// gl_draw_background(img, gl_color_(color));








	// update frame buffer instance. 
	// NOTE: mlx_do_sync가 프레임 버퍼링 깜빡거림 현상을 해결할 수 있다고 하는데...
	// NOTE: 아직 이게 뭘 해주는지 잘 모르겠음.
	// mlx_do_sync(device->mlx);
	return (0);
}