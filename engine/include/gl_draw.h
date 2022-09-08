/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:57:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/08 19:35:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DRAW_H
# define GL_DRAW_H

/* NOTE: deleted #ifndef macro, because of -I include option */
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

/* Default Coordinate system: from (Screen Width ~ Screen Height). */
extern void	gl_draw_pixel(t_image *image, int _x, int _y, int _argb);

/* Returns integer pointer of target Pixel(x, y) */
extern int	*gl_get_pixel_addr(t_image *_image, const int _x, const int _y);

/* Fill every pixel of the image with (int _argb) color. */
extern void	gl_draw_background(t_image *image, int _argb);

/* Draw line from Point v1(x1, y1) to Point v2(x2, y2) */
extern void	gl_draw_line(t_image *image, t_vec2 _p1, t_vec2 _p2, int _argb);

#endif /* GL_DRAW_H */
