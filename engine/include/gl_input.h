/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:44:40 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:22:26 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INPUT_H
# define GL_INPUT_H

# include <stdbool.h>
# include <stddef.h>
# if defined (__linux__)
#  define PLATFORM_NAME (__LINUX__)
#  include "mlx_keymap_linux.h"
# elif defined (__APPLE__)
#  define PLATFORM_NAME (__OSX__)
#  include "mlx_keymap_macos.h"
# endif
# include "gl_device.h"

/* #engine/gl_core/
 * -  NOTE: Use this function only for keyboard-input checking.
 * - Returns true (1) if key_code passed as argument is down (= pressed).
 * - Else, function returns false (0). */
extern int		input_is_key_down(t_device *device, int key_code);

/* #engine/gl_core/
 * -  NOTE: Use this function only for keyboard-input checking.
 * - Returns true(1) if key_code passed as argument is up (= unpressed)
 * - Else, function returns false (0). */
extern int		input_is_key_unpressed(t_device *device, int key_code);

/* #engine/gl_core/
 * -  NOTE: Use this function only for Mouse-input checking.
 * - Returns true(1) if key_code passed as argument is down (=pressed)
 * - Else, function returns false (0)*/
extern int		input_is_mouse_down(t_device *device, int key_code);

/* #engine/gl_core/
 * -  NOTE: Use this function only for Mouse-input checking.
 * - Returns true(1) if key_code passed as argument is up (= unpressed)
 * - Else, function returns false (0)*/
extern int		input_is_mouse_unpressed(t_device *device, int key_code);

/* #engine/gl_core/
 * - Get mouse position and return as t_vec2 type data. (x, y) */
extern t_vec2	input_get_mouse_pos(const t_device *device);

#endif /* INPUT_H */
