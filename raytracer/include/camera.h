/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:44:22 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 23:38:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "gl_vec3.h"
#include "gl_vec2.h"
#include "libft.h"
#include "gl_device.h"

typedef struct s_camera {

	bool 	has_camera;

	t_vec3	pos; // position of camera (x, y, z)
	t_vec3	look_at; // orientation of camera (normalized vector)
	float	fov; // FOV (range from 0 to 180)

	t_vec3	up_direction; // up direction
	t_vec3	right_direction; // up direction
	t_vec3  projection_screen_center; // center of projection screen
	float   camera_length;

}	t_camera;

void update_camera_geometry(t_device *device);

t_vec3 transform_screen_to_camera_world(t_camera *camera, t_image *img, t_vec2 pos_screen);

#endif /** camera.h */
