/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:29:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 16:42:57 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

/** static float	abs(float x) */
/** { */
/**     if (x > 0) */
/**         return (x); */
/**     else */
/**         return (-x); */
/** } */

/** TODO: delete later  */
#include <stdio.h>

void	gl_draw_line(t_image *image, t_vec2 p1, t_vec2 p2, int _argb)
{
	unsigned int	ndots;
	float			t;
	float			offset;

	t_vec2	p = gl_get_vec2_from_2f(p2.x - p1.x, p2.y - p1.y);
	ndots = gl_vec2_get_magnitude(p);
	t = 0;
	while (t < ndots)
	{
		offset = t / ndots;
		p.x = ((1 - offset) * p1.x) + (offset * p2.x);
		p.y = ((1 - offset) * p1.y) + (offset * p2.y);
		gl_draw_pixel(image, p.x, p.y, _argb);
		t += 1;
	}
}

/** FIX: 얘는 엄청난 오차 발생 ㅋ */
/** void	gl_draw_line(t_image *image, t_vec2 _v1, t_vec2 _v2, int _argb) */
/** { */
/**     t_vec2	direction; */
/**     float	x; */
/**     float	y; */
/**  */
/**     // FIX: ? */
/**     direction = gl_vec2_normalize(gl_vec2(_v2.x - _v1.x, _v2.y - _v1.y)); */
/**     x = _v1.x * image->width; */
/**     y = _v1.y * image->height; */
/**     while (_v2.x > _v1.x && abs(_v2.x * image->width) - abs(x) > 1.0f) */
/**     { */
/**         x += direction.x; */
/**         y += direction.y; */
/**         gl_draw_pixel(image, x, y, _argb); */
/**     } */
/**     while (_v2.x < _v1.x && abs(x) - abs(_v2.x * image->width) > 1.0f) */
/**     { */
/**         x += direction.x; */
/**         y += direction.y; */
/**         gl_draw_pixel(image, x, y, _argb); */
/**     } */
/** } */

/** static void	bezier_linear(t_device *device, t_point3d p1, t_point3d p2) */
/** { */
/**     unsigned int	ndots; */
/**     float			t; */
/**     float			offset; */
/**     t_point3d		point; */
/**     t_vector4		vec_p1p2; */
/**  */
/**     vec_p1p2 = create_vector4(p2.cord.x - p1.cord.x, \ */
/**             p2.cord.y - p1.cord.y, p2.cord.z - p1.cord.z, 0); */
/**     ndots = get_magnitude_vec4(vec_p1p2); */
/**     t = 0; */
/**     while (t < ndots) */
/**     { */
/**         offset = t / ndots; */
/**         point.cord.x = ((1 - offset) * p1.cord.x) + (offset * p2.cord.x); */
/**         point.cord.y = ((1 - offset) * p1.cord.y) + (offset * p2.cord.y); */
/**         point.cord.z = ((1 - offset) * p1.cord.z) + (offset * p2.cord.z); */
/**         point.color = color_shader(fdf, get_cord_color(p1, p2, offset), \ */
/**                 point.cord.z); */
/**         draw_pixel(fdf, point); */
/**         t += 1; */
/**     } */
/** } */
/**  */
/** void	draw_line(t_mlx *fdf, t_point3d _p1, t_point3d _p2) */
/** { */
/**     bezier_linear(fdf, _p1, _p2); */
/** } */
