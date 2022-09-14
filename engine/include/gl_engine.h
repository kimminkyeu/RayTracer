/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_engine.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:48:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 14:58:13 by minkyeki         ###   ########.fr       */
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
extern t_device	*engine_init(int _win_width, int _win_height, char *title);

/* #src/engine_core/engine.c */
extern void		engine_exit(t_device *device, bool is_error);

/* #src/engine_core/engine.c */
extern void	    engine_new_image(t_device *device, t_vec2 img_size, t_vec2 img_location, int (*f_update_func)());


/* #src/engine_core/engine.c
저장된 이미지 배열을 순회하면서 해당 이미지들을 모두 업데이트 한뒤, window에 push한다. */
extern int	    engine_update_images(t_device *device);

/* #src/engine_core/engine.c
이미지를 window에 그린다.*/
extern void		engine_push_image(t_device *device, t_image *image, int x, int y);

/* #src/engine_core/engine.c */
extern void     engine_render(t_device *device);

#endif /* ENGINE_H */
