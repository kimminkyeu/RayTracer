/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:06:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:10:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "gl_device.h"
# include "objects.h"

# define TEXTURE_CHECKER 	(0)
# define TEXTURE_GRADIENT 	(1)
# define TEXTURE_FILE 		(2)

typedef struct s_texture {
	int			width;
	int			height;
	t_image		image;
	int			type;
}	t_texture;

/* allocate new texture data */
extern t_texture	*new_texture(t_device *device, char *filename);

/* allocate new texture data with checkerboard.*/
extern t_texture	*new_texture_checkerboard(t_device *device, int width, \
												int height);

/* Normal Mapping */
extern t_vec3		sample_normal_map(const t_hit *hit);

extern t_vec3		sample_point(t_texture *texture, \
									const t_vec2 uv, int is_raw);
extern t_vec3		sample_linear(t_texture *texture, \
									const t_vec2 uv, int is_raw);

#endif /** texture.h */
