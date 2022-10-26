/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:57:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:31:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DRAW_H
# define GL_DRAW_H

# include "gl_vec2.h"
# include "gl_vec4.h"
# include "gl_device.h"

# define __LINUX__	(0)
# define __OSX__	(1)

# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__)
#  include "gl_keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "gl_keymap_macos.h"
# endif

/* Returns integer pointer of target Pixel(x, y) */
extern int		*gl_get_pixel_addr(t_image *image, int x, int y);

/* Returns [int argb] color-value of pixel:(x, y).
 if (x, y) is off-range of image_width/height,
 clamped (x', y') pixel color is returned.
 for example, color of (-1, -1) becomes color of (0, 0). */
extern int		gl_get_pixel_color_int(t_image *image, int x, int y);

/* Returns [t_vec4] color-value of pixel:(x, y) */
extern t_vec4	gl_get_pixel_color_vec4(t_image *image, int x, int y);

/* Default Coordinate system: from (Screen Width ~ Screen Height). */
extern void		gl_draw_pixel(t_image *image, int x, int y, int argb);

/* Fill every pixel of the image with (int _argb) color. */
extern void		gl_draw_background(t_image *image, int argb);

/* Draw line from Point v1(x1, y1) to Point v2(x2, y2) */
extern void		gl_draw_line(t_image *image, t_vec2 point_1, \
								t_vec2 point_2, int argb);

#endif /* GL_DRAW_H */
