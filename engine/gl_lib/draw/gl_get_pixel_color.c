/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_get_pixel_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:29:25 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/15 14:07:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec4.h"

static int	clamp(int num, int min, int max)
{
	if (num < min)
		return (min);
	else if (num > max)
		return (max);
	else
		return (num);
}

int		gl_get_pixel_color_int(t_image *image, int x, int y)
{
//   x = clamp(x, 0, image->img_size.width);
//   y = clamp(x, 0, image->img_size.height);
  return (*(gl_get_pixel_addr(image, x, y)));
}

t_vec4	gl_get_pixel_color_vec4(t_image *image, int x, int y)
{
	int	color;

	x = clamp(x, 0, image->img_size.width - 1);
	y = clamp(y, 0, image->img_size.height - 1);
	color = gl_get_pixel_color_int(image, x, y);
	return (gl_get_vec4_from_color(color));
}
