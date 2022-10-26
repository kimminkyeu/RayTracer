/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:29:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:01:03 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_draw.h"

void	gl_draw_line(t_image *image, t_vec2 p1, t_vec2 p2, int _argb)
{
	unsigned int	ndots;
	float			t;
	float			offset;
	t_vec2			p;

	p = gl_vec2_2f(p2.x - p1.x, p2.y - p1.y);
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
