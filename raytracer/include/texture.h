/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:06:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 15:08:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "gl_device.h"

typedef struct s_texture {

	int 		width;
	int 		height;
	int 		channels;

	t_image*	image; // texture image.

}	t_texture;


#endif /** texture.h */
