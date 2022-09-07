/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:48:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/04 22:17:57 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdlib.h>					/* for Exit */
# include <stdio.h>						/* for Perror */
# include <stdbool.h>					/* for isError flag */

# define __LINUX__	(0)
# define __OSX__	(1)

# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__) 
#  include "../../../mlx_linux/mlx.h"
#  include "keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "../../../mlx_mms/mlx.h"
#  include "keymap_macos.h"
# endif

/* Engine Header */
# include "device.h"
# include "input.h"
# include "../../libft/include/libft.h"
# include "../analysis/time.h"
# include "../gl_lib/color/gl_color.h"
# include "../gl_lib/math/gl_matrix.h"
# include "../gl_lib/math/gl_vec2.h"
# include "../gl_lib/math/gl_vec4.h"
# include "../gl_lib/draw/gl_draw.h"

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
