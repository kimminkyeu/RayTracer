/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:06:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 22:09:34 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "gl_device.h"
#include "objects.h"


typedef struct s_texture {

	int 		width;
	int 		height;
	t_image		image; // texture image.
	// int 		channels;

}	t_texture;

// allocate new texture data
extern t_texture	*new_texture(t_device *device, char* filename);
// allocate new texture data with checkerboard.
extern t_texture	*new_texture_checkerboard(t_device *device, int width, int height);

extern t_vec3 get_clamped(t_texture *texture, int i, int j);

extern t_vec3 get_wrapped(t_texture *texture, int i, int j);

extern t_vec3 interpolate_bilinear(
	const float dx,
	const float dy,
	const t_vec3 c00,
	const t_vec3 c10,
	const t_vec3 c01,
	const t_vec3 c11);

extern t_vec3 sample_point(t_texture *texture, const t_vec2 uv); // Nearest sampling이라고 부르기도 함

extern t_vec3 sample_linear(t_texture *texture, const t_vec2 uv);

#endif /** texture.h */
