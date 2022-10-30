/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:44:22 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:06:35 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "gl_vec3.h"
# include "gl_vec2.h"
# include "libft.h"
# include "gl_device.h"

typedef struct s_camera {
	bool	has_camera;
	t_vec3	pos;
	t_vec3	look_at;
	float	fov;
	t_vec3	up_direction;
	t_vec3	right_direction;
	t_vec3	projection_screen_center;
	float	camera_length;
	t_vec2	rotation_delta;
}	t_camera;

void	update_camera_geometry(t_device *device);

t_vec3	transform_screen_to_camera_world(t_camera *camera, t_image *img, \
										t_vec2 pos_screen);

#endif /** camera.h */
