/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:57:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 16:44:17 by sungjpar         ###   ########seoul.kr  */
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

/* Fill every pixel of the image with (int _argb) color. */
extern void	gl_draw_background(t_image *image, int _argb);

/* Add description */
extern void	gl_draw_line(t_image *image, t_vec2 _v1, t_vec2 _v2, int _argb);

#endif /* GL_DRAW_H */
