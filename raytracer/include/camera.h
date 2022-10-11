/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:44:22 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 14:52:39 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "gl_vec3.h"

typedef struct s_camera {

	bool 	has_camera;

	t_vec3	pos; // position of camera (x, y, z)
	t_vec3	dir; // orientation of camera (normalized vector)
	float	fov; // FOV (range from 0 to 180)

}	t_camera;

#endif /** camera.h */
