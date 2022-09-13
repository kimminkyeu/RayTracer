/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:48:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/13 13:20:30 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_ENGINE_H
# define GL_ENGINE_H

# include <stdlib.h>					/* for Exit */
# include <stdio.h>						/* for Perror */
# include <stdbool.h>					/* for isError flag */

# define __LINUX__	(0)
# define __OSX__	(1)

# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__) 
#  include "mlx_linux.h"
#  include "gl_keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "mlx_macos.h"
#  include "gl_keymap_macos.h"
# endif

/* Engine Header */
# include "libft.h"
# include "gl_device.h"
# include "gl_input.h"
# include "gl_time.h"
# include "gl_color.h"
# include "gl_matrix.h"
# include "gl_vec2.h"
# include "gl_vec3.h"
# include "gl_vec4.h"
# include "gl_draw.h"
# include "gl_shader.h"

# define STDOUT				(1)
# define ERROR				(1)
# define SUCCESS			(0)

/* #src/engine_core/engine.c */
extern t_device	*engine_init(int _viewport_width, int _panel_width, int _win_height, char *title);

/* #src/engine_core/engine.c */
extern void		engine_exit(t_device *device, bool is_error);

/* #src/engine_core/engine.c */
extern void		engine_start_loop(t_device *device, int (*render_layer)());

/* #src/engine_core/engine.c */
extern void		engine_set_key_event(t_device *device, int (*f_key_press)(), int (*f_key_release)());

/* #src/engine_core/engine.c */
extern void		engine_set_mouse_event(t_device *device, int (*f_mouse_press)(), int (*f_mouse_release)());

    /* #src/engine_core/engine.c */
extern void		engine_push_image(t_device *device, t_image *image, int x, int y);

#endif /* ENGINE_H */
